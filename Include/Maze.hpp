#pragma once

#include <array>
#include <vector>

#include "CellIterator.hpp"
#include "DrawFrame.hpp"
#include "Shape.hpp"
#include "Window.hpp"

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

const static std::array<Direction, WALL_COUNT> DIRECTIONS = {Direction{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const static std::array<Wall, WALL_COUNT> WALLS = {NORTH, WEST, SOUTH, EAST};
const static std::array<Wall, WALL_COUNT> OPPOSITE_WALL = {SOUTH, EAST, NORTH, WEST};

class Maze
{
  public:
    Maze(Shape shape, Cell start, Cell end);

    MazeCellIterator begin() const;
    MazeCellIterator end() const;

    int RavelCell(Cell cell) const;
    const unsigned char &At(Cell cell) const;
    unsigned char &At(Cell cell);
    void RemoveWall(Cell cell, Wall wall);
    int Cols() const;
    int Rows() const;
    Cell StartCell() const;
    Cell EndCell() const;
    bool HasWall(Cell cell, Wall wall) const;
    bool OutOfBounds(Cell cell);

  private:
    void _RemoveWall(Cell cell, Wall wall);

  public:
    Shape m_Shape;
    Cell m_Start;
    Cell m_End;
    std::vector<unsigned char> m_Cells;
};

Shape GetCellShape(const Window &window, const Maze &maze);

} // namespace xmaze
