#include <SFML/Graphics.hpp>
#include <fmt/core.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

int main()
{
    spdlog::set_default_logger(spdlog::stderr_color_st("logger"));
    spdlog::set_pattern("[%H:%M:%S %z] [%^-%L-%$] %v");
    spdlog::set_level(spdlog::level::debug);

    fmt::println("Hello from 'tetris-cpp'!");

    auto videoMode = sf::VideoMode{ 800, 600 };
    auto window    = sf::RenderWindow{ videoMode, "Tetris" };

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(true);
    window.setActive(true);

    while (window.isOpen()) {
        for (sf::Event event{}; window.pollEvent(event);) {
            using E = sf::Event;
            using K = sf::Keyboard::Key;

            switch (event.type) {
            case E::Closed: window.close(); break;
            case E::KeyPressed: {
                if (event.key.code == K::Q) {
                    window.close();
                }
            } break;
            default: /* do nothing */ break;
            }
        }

        window.clear(sf::Color::Magenta);

        // draw here ...

        window.display();
    }
}
