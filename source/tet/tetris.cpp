#include "tet/tetris.hpp"

#include <SFML/Window.hpp>

#include <chrono>
#include <cmath>
#include <limits>

namespace chr = std::chrono;

namespace
{
    auto toMicros(tet::usize fps)
    {
        using namespace std::chrono_literals;
        using FloatSeconds = chr::duration<tet::f32>;
        auto duration      = FloatSeconds{ 1 } / static_cast<tet::f32>(fps);
        return chr::duration_cast<chr::microseconds>(duration);
    }

    tet::f32 toFps(auto duration)
    {
        using FloatSecond = chr::duration<tet::f32>;
        auto seconds      = chr::duration_cast<FloatSecond>(duration).count();
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

        void reset() { m_last = tet::Clock::now(); }

        tet::Duration elapsed()
        {
            auto now   = tet::Clock::now();
            auto delta = now - m_last;
            m_last     = now;
            return chr::duration_cast<tet::Duration>(delta);
        }

    private:
        tet::Clock::time_point m_last = tet::Clock::now();
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
                auto time  = chr::duration_cast<chr::duration<float>>(elapsed).count();

                // funny color cycle
                auto r = (std::sin(23.0f / 8.0f * time) + 1.0f) * 0.1f + 0.4f;
                auto g = (std::cos(13.0f / 8.0f * time) + 1.0f) * 0.2f + 0.3f;
                auto b = (std::sin(41.0f / 8.0f * time) + 1.5f) * 0.2f;

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
