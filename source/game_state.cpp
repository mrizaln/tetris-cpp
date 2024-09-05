#include "game_state.hpp"

#include <fmt/core.h>

namespace tet
{
    GameState::GameState(async::Context& context)
        : m_timer{ context }
    {
    }

    async::Task<void> GameState::update()
    {
        m_timer.expires_after(m_delay);

        fmt::println("GameState is being updated...");

        co_await m_timer.async_wait();
    }
}
