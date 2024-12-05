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

const static std::array<Direction, WALL_COUNT> DIRECTIONS = {Direction{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const static std::array<Wall, WALL_COUNT> WALLS = {NORTH, WEST, SOUTH, EAST};
const static std::array<Wall, WALL_COUNT> OPPOSITE_WALL = {SOUTH, EAST, NORTH, WEST};

class Maze
{
  public:
    Maze(Shape shape, Cell start, Cell end) : m_Shape(shape), m_Start(start), m_End(end)
    {
        const unsigned char ALL_WALLS = NORTH_BIT | WEST_BIT | SOUTH_BIT | EAST_BIT;
        const size_t CELL_COUNT = m_Shape.height * m_Shape.width;

        m_Cells.reserve(CELL_COUNT);
        std::fill_n(std::back_inserter(m_Cells), CELL_COUNT, ALL_WALLS);
    }

    inline int RavelIndex(int x, int y) const
    {
        return x + y * m_Shape.width;
    }

    inline size_t RavelIndex(size_t x, size_t y) const
    {
        return x + y * m_Shape.width;
    }

    inline int RavelCell(Cell cell) const
    {
        return RavelIndex(cell.x, cell.y);
    }

    inline const unsigned char &At(size_t x, size_t y) const
    {
        return m_Cells[RavelIndex(x, y)];
    }

    inline unsigned char &At(size_t x, size_t y)
    {
        return m_Cells[RavelIndex(x, y)];
    }

    inline const unsigned char &At(Cell cell) const
    {
        return At(cell.x, cell.y);
    }

    inline unsigned char &At(Cell cell)
    {
        return At(cell.x, cell.y);
    }

    inline void RemoveWall(Cell cell, Wall wall)
    {
        _RemoveWall(cell, wall);
        _RemoveWall(cell + DIRECTIONS[wall], OPPOSITE_WALL[wall]);
    }

    inline size_t Cols() const
    {
        return m_Shape.width;
    }

    inline size_t Rows() const
    {
        return m_Shape.height;
    }

    Cell StartCell() const
    {
        return m_Start;
    }

    Cell EndCell() const
    {
        return m_End;
    }

    inline bool OutOfBounds(Cell cell)
    {
        const int width = m_Shape.width;
        const int height = m_Shape.height;
        return cell.x < 0 || cell.x >= width || cell.y < 0 || cell.y >= height;
    }

  private:
    inline void _RemoveWall(Cell cell, Wall wall)
    {
        if (!OutOfBounds(cell))
        {
            unsigned char &walls = At(cell);
            walls &= ~WALL_BITS[wall];
        }
    }

  public:
    Shape m_Shape;
    Cell m_Start;
    Cell m_End;
    std::vector<unsigned char> m_Cells;
};

void DrawCell(Cell cell, Shape cell_shape, const char *color, const Window &window, Pixmap &pixmap);
void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap);

Shape GetCellShape(const Window &window, const Maze &maze);

} // namespace xmaze
