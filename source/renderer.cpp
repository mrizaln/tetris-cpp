#include "renderer.hpp"
#include <fmt/core.h>

namespace tet
{
    async::Task<void> Renderer::draw(sf::RenderTarget& target)
    {
        fmt::println("renderer draws stuff...");
        co_return;
    }
}
