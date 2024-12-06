#pragma once

#include <array>
#include <cstddef>
#include <functional>

#include "Point.hpp"

using Cell = Point<int>;

const static Cell INVALID_CELL = Cell{-1, -1};

namespace std
{
template <> struct hash<Cell>
{
    size_t operator()(const Cell &cell) const
    {
        auto hasher = hash<int>();
        std::size_t h1 = hasher(cell.x);
        std::size_t h2 = hasher(cell.y);
        h1 ^= hasher(h2) + 0x9e3779b9 + (h1 << 6) + (h1 >> 2);
        return h1;
    }
};
} // namespace std

using Direction = Point<int>;

static const size_t WALL_COUNT = 4;

enum class Wall
{
    NORTH = 0,
    WEST,
    SOUTH,
    EAST
};

const static std::array<Wall, WALL_COUNT> WALLS = {Wall::NORTH, Wall::WEST, Wall::SOUTH, Wall::EAST};

const static std::array<Direction, WALL_COUNT> DIRECTIONS = {Direction{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
inline Direction GetDirection(Wall wall)
{
    return DIRECTIONS[static_cast<int>(wall)];
}
