#include "tet/block.hpp"

void printCollision(const tet::BlockCollision& collision)
{
    auto [width, height] = tet::BlockCollision::s_cells;
    for (auto y : tet::rv::iota(0uz, height)) {
        fmt::print("\t\t");
        for (auto x : tet::rv::iota(0uz, width)) {
            fmt::print("{}", collision[x, y] ? "⬛" : "⬜");
        }
        fmt::println("");
    }
}

int main()
{
    for (auto [kind, name] : magic_enum::enum_entries<tet::BlockKind>()) {
        auto block = tet::Block(kind, 0);

        for (auto i : tet::rv::iota(0uz, tet::Block::s_rotationNum)) {
            const auto& collision = block.collision();
            fmt::println("Tetromino: {} (variant {})", name, i);
            printCollision(collision);
            block.rotate();
            fmt::println("");
        }
    }
}
