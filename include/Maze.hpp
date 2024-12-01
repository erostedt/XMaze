#pragma once

#include <algorithm>
#include <array>

#include <iterator>
#include <vector>

#include <Pixmap.hpp>
#include <Shape.hpp>
#include <Window.hpp>

namespace xmaze
{

static const size_t WALL_COUNT = 4;

enum Wall
{
    NORTH = 0,
    WEST,
    SOUTH,
    EAST
};

enum WallBit
{
    NORTH_BIT = 1 << NORTH,
    WEST_BIT = 1 << WEST,
    SOUTH_BIT = 1 << SOUTH,
    EAST_BIT = 1 << EAST,
};

static unsigned char WALL_BITS[] = {
    NORTH_BIT,
    WEST_BIT,
    SOUTH_BIT,
    EAST_BIT,
};

const static std::array<Direction, WALL_COUNT> DIRECTIONS = {Direction{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
const static std::array<Wall, WALL_COUNT> OPPOSITE_WALL = {SOUTH, EAST, NORTH, WEST};

class Maze
{
  public:
    Maze(Shape shape_) : shape(shape_)
    {
        unsigned char ALL_WALLS = WALL_BITS[NORTH] | WALL_BITS[WEST] | WALL_BITS[SOUTH] | WALL_BITS[EAST];
        size_t CELL_COUNT = shape.height * shape.width;

        Cells.reserve(CELL_COUNT);
        std::fill_n(std::back_inserter(Cells), CELL_COUNT, ALL_WALLS);
    }

    const unsigned char &At(size_t x, size_t y) const
    {
        return Cells[x + y * shape.width];
    }

    unsigned char &At(size_t x, size_t y)
    {
        return Cells[x + y * shape.width];
    }

    const unsigned char &At(Cell cell) const
    {
        return At(cell.x, cell.y);
    }

    unsigned char &At(Cell cell)
    {
        return At(cell.x, cell.y);
    }

    void RemoveWall(Cell cell, Wall wall)
    {
        _RemoveWall(cell, wall);
        _RemoveWall(cell + DIRECTIONS[wall], OPPOSITE_WALL[wall]);
    }

  private:
    void _RemoveWall(Cell cell, Wall wall)
    {
        if (!OutOfBounds(cell))
        {
            unsigned char &walls = At(cell);
            walls &= ~WALL_BITS[wall];
        }
    }

    bool OutOfBounds(Cell cell)
    {
        const int width = shape.width;
        const int height = shape.height;
        return cell.x < 0 || cell.x >= width || cell.y < 0 || cell.y >= height;
    }

  public:
    Shape shape;
    std::vector<unsigned char> Cells;
};

void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap);

} // namespace xmaze
