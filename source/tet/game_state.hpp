#pragma once

#include "tet/async/async.hpp"
#include "tet/common.hpp"

namespace tet
{
    class GameState
    {
    public:
        GameState(async::Context& context);
        ~GameState() = default;

        GameState(GameState&&)                 = delete;
        GameState(const GameState&)            = delete;
        GameState& operator=(const GameState&) = delete;
        GameState& operator=(GameState&&)      = delete;

        auto              delay() const { return m_delay; }
        async::Task<void> update();

    private:
        static constexpr auto s_defaultDelay = Duration{ 100 };

        Duration     m_delay = s_defaultDelay;
        async::Timer m_timer;
    };
}
