#pragma once

#include "game_state.hpp"
#include "renderer.hpp"

#include "async/async.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

namespace tet
{
    class Tetris
    {
    public:
        Tetris()  = delete;
        ~Tetris() = default;

        Tetris(Tetris&&)                 = delete;
        Tetris& operator=(Tetris&&)      = delete;
        Tetris(const Tetris&)            = delete;
        Tetris& operator=(const Tetris&) = delete;

        Tetris(sf::VideoMode videoMode, std::string_view title);

        void run();

    private:
        static constexpr usize s_defaultFrameLimit = 60;

        async::Task<void> renderingLoop();
        async::Task<void> gameUpdateLoop();

        void handleInputs();

        async::Context   m_context;
        sf::RenderWindow m_window;

        Renderer  m_renderer;
        GameState m_gameState;

        std::string_view m_title      = "No title";
        bool             m_running    = false;
        usize            m_frameLimit = s_defaultFrameLimit;
    };
}
