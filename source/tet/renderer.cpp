#include "tet/renderer.hpp"

#include <spdlog/spdlog.h>

namespace tet
{
    async::Task<void> Renderer::draw(sf::RenderTarget& target)
    {
        spdlog::debug("renderer draws stuff...");
        co_return;
    }
}
