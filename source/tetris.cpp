#include "tetris.hpp"

#include <SFML/Window.hpp>

#include <cmath>
#include <limits>

namespace
{
    auto toMicros(tet::usize fps)
    {
        using namespace std::chrono_literals;
        using FloatMillis = std::chrono::duration<tet::f32, std::milli>;
        auto duration     = FloatMillis{ 1000 } / static_cast<tet::f32>(fps);
        return std::chrono::duration_cast<std::chrono::microseconds>(duration);
    }

    tet::f32 toFps(auto duration)
    {
        using FloatSecond = std::chrono::duration<tet::f32>;
        auto seconds      = std::chrono::duration_cast<FloatSecond>(duration).count();
        return 1.0F / seconds;
    }

    sf::Color toColor(tet::f32 r, tet::f32 g, tet::f32 b, tet::f32 a)
    {
        auto toHex = [](tet::f32 v) { return static_cast<tet::u8>(v * std::numeric_limits<tet::u8>::max()); };
        return { toHex(r), toHex(g), toHex(b), toHex(a) };
    }

    class DeltaTimer
    {
    public:
        DeltaTimer() = default;

        void reset() { m_last = m_clock.now(); }

        tet::Duration elapsed()
        {
            auto now   = m_clock.now();
            auto delta = now - m_last;
            m_last     = now;
            return std::chrono::duration_cast<tet::Duration>(delta);
        }

    private:
        tet::Clock             m_clock = {};
        tet::Clock::time_point m_last  = m_clock.now();
    };
}

namespace tet
{
    Tetris::Tetris(sf::VideoMode videoMode, std::string_view title)
        : m_window{ videoMode, title.data() }
        , m_gameState{ m_context }
        , m_title{ title }
    {
        m_window.setVerticalSyncEnabled(false);
        m_window.setKeyRepeatEnabled(true);
        m_window.setActive(true);
    }

    void Tetris::run()
    {
        m_running = true;

        async::spawn(m_context, renderingLoop());
        async::spawn(m_context, gameUpdateLoop());

        m_context.run();
    }

    async::Task<void> Tetris::renderingLoop()
    {
        using namespace std::chrono_literals;

        auto asyncTimer = async::Timer{ m_context };
        auto deltaTimer = DeltaTimer{};
        auto elapsed    = 0ms;

        while (m_running and m_window.isOpen()) {
            asyncTimer.expires_after(toMicros(m_frameLimit));

            handleInputs();

            // actual draw
            {
                elapsed   += deltaTimer.elapsed();
                auto time  = static_cast<f32>(elapsed.count());

                // funny color cycle
                auto r = (std::sin(23.0F / 8.0F * time) + 1.0F) * 0.1F + 0.4F;
                auto g = (std::cos(13.0F / 8.0F * time) + 1.0F) * 0.2F + 0.3F;
                auto b = (std::sin(41.0F / 8.0F * time) + 1.5F) * 0.2F;

                m_window.clear(toColor(r, g, b, 1.0F));
                co_await m_renderer.draw(m_window);
                m_window.display();
            }

            co_await asyncTimer.async_wait();
        }

        m_running = false;
    }

    async::Task<void> Tetris::gameUpdateLoop()
    {
        while (m_running) {
            co_await m_gameState.update();
        }
    }

    void Tetris::handleInputs()
    {
        auto event = sf::Event{};
        while (m_window.pollEvent(event)) {
            using E = sf::Event;
            using K = sf::Keyboard::Key;

            switch (event.type) {
            case E::Closed: {
                m_window.close();
                m_running = false;
            } break;
            case E::KeyPressed: {
                if (event.key.code == K::Q) {
                    m_window.close();
                    m_running = false;
                }
            } break;
            default: /* do nothing */ break;
            }
        }
    }
}
