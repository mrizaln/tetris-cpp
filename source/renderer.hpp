#pragma once

#include "async/async.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace tet
{
    class Renderer
    {
    public:
        // temporary
        Renderer()  = default;
        ~Renderer() = default;

        Renderer(Renderer&&)                 = delete;
        Renderer& operator=(Renderer&&)      = delete;
        Renderer(const Renderer&)            = delete;
        Renderer& operator=(const Renderer&) = delete;

        async::Task<void> draw(sf::RenderTarget& target);
    };
}
