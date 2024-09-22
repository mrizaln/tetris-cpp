#include "tet/block.hpp"

#include <magic_enum.hpp>

namespace tet::collisions
{
    consteval auto fromInteger(std::array<usize, Block::s_rotationNum> integers)
    {
        auto collisions = std::array<BlockCollision, Block::s_rotationNum>{};

        auto parse = [](usize integer) consteval {
            auto cells = BlockCollision::Cells{};
            for (auto i : rv::iota(0uz, BlockCollision::s_area)) {
                auto index   = BlockCollision::s_area - i - 1;
                cells[index] = ((integer & (1 << i)) != 0u);
            }
            return BlockCollision{ cells };
        };

        for (auto [i, v] : integers | rv::enumerate) {
            collisions[static_cast<usize>(i)] = parse(v);
        }

        return collisions;
    }

    // clang-format off
    constexpr auto I = fromInteger({ 0b010'010'010, 0b000'111'000, 0b010'010'010, 0b000'111'000 });
    constexpr auto O = fromInteger({ 0b110'110'000, 0b110'110'000, 0b110'110'000, 0b110'110'000 });
    constexpr auto T = fromInteger({ 0b010'111'000, 0b010'011'010, 0b000'111'010, 0b010'110'010 });
    constexpr auto L = fromInteger({ 0b001'111'000, 0b010'010'011, 0b000'111'100, 0b110'010'010 });
    constexpr auto J = fromInteger({ 0b100'111'000, 0b011'010'010, 0b000'111'001, 0b010'010'110 });

    // TODO: maybe make variant 2 and 3 a proper rotation instead of copying 0 and 1
    constexpr auto S = fromInteger({ 0b011'110'000, 0b100'110'010, 0b011'110'000, 0b100'110'010 });
    constexpr auto Z = fromInteger({ 0b110'011'000, 0b010'110'100, 0b110'011'000, 0b010'110'100 });
    // clang-format on

    constexpr const auto& getCollision(BlockKind kind)
    {
        switch (kind) {
        case BlockKind::I: return collisions::I;
        case BlockKind::O: return collisions::O;
        case BlockKind::T: return collisions::T;
        case BlockKind::L: return collisions::L;
        case BlockKind::J: return collisions::J;
        case BlockKind::S: return collisions::S;
        case BlockKind::Z: return collisions::Z;
        default: return collisions::O;
        }
    }
}

namespace tet
{
    Block Block::random()
    {
        auto kindNum  = magic_enum::enum_count<BlockKind>();
        auto kindIdx  = static_cast<int>(tet::random(0uz, kindNum - 1));
        auto kind     = magic_enum::enum_cast<BlockKind>(kindIdx).value_or(BlockKind::O);
        auto rotation = tet::random(0uz, s_rotationNum - 1);

        return { kind, rotation };
    }

    Block& Block::rotate(bool counterClockwise)
    {
        if (not counterClockwise) {
            m_rotationIndex = (m_rotationIndex + 1) % s_rotationNum;
        } else {
            m_rotationIndex = (m_rotationIndex + (s_rotationNum - 1)) % s_rotationNum;
        }
        return *this;
    }

    const BlockCollision& Block::collision() const
    {
        const auto& collisions = collisions::getCollision(m_kind);
        return collisions[m_rotationIndex];
    }
}
