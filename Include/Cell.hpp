#pragma once

#include <array>
#include <cstddef>

#include "Point.hpp"

using Cell = Point<int>;
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
