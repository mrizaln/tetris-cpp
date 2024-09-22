#pragma once

#include "tet/common.hpp"

#include <array>

namespace tet
{
    struct BlockCollision
    {
    public:
        static constexpr std::pair<usize, usize> s_cells = { 3, 3 };
        static constexpr usize                   s_area  = s_cells.first * s_cells.second;

        using Cells = std::array<bool, s_area>;

        constexpr BlockCollision() = default;
        constexpr BlockCollision(Cells cells)
            : m_cells{ cells }
        {
        }

        constexpr bool operator[](usize x, usize y) const
        {
            auto [width, _] = BlockCollision::s_cells;
            auto index      = y * width + x;
            return m_cells[index];
        }

    private:
        Cells m_cells = {};
    };

    enum class BlockKind : int
    {
        I,
        O,
        T,
        L,
        J,
        S,
        Z,
    };

    class Block
    {
    public:
        static constexpr usize s_rotationNum = 4;

        Block(BlockKind kind, usize rotation)
            : m_kind{ kind }
            , m_rotationIndex{ rotation }
        {
        }

        static Block random();

        Block&                rotate(bool counterClockwise = false);
        const BlockCollision& collision() const;

    private:
        BlockKind m_kind;
        usize     m_rotationIndex = 0;
    };
}
