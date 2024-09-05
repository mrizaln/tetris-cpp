#include "tet/tetris.hpp"

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
    auto tetris    = tet::Tetris{ videoMode, "Tetris" };

    tetris.run();
}
