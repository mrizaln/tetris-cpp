#include "tet/tetris.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

void configureLogger()
{
    spdlog::set_default_logger(spdlog::stderr_color_st("logger"));
    spdlog::set_pattern("[%H:%M:%S %z] [%^-%L-%$] %v");
    spdlog::set_level(spdlog::level::debug);
}

int main()
{
    configureLogger();

    const auto videoMode = sf::VideoMode{ 1280, 720 };

    auto tetris = tet::Tetris{ videoMode, "Tetris" };
    tetris.run();
}
