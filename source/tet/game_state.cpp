#include "tet/game_state.hpp"

#include <spdlog/spdlog.h>

namespace tet
{
    GameState::GameState(async::Context& context)
        : m_timer{ context }
    {
    }

    async::Task<void> GameState::update()
    {
        m_timer.expires_after(m_delay);

        spdlog::debug("GameState is being updated...");

        co_await m_timer.async_wait();
    }
}
