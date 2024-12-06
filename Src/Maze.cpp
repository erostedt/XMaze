#include <X11/Xlib.h>

#include "DrawFrame.hpp"
#include "Maze.hpp"
#include "Window.hpp"

namespace XMaze
{

enum WallBit
{
    NORTH_BIT = 1 << static_cast<int>(Wall::NORTH),
    WEST_BIT = 1 << static_cast<int>(Wall::WEST),
    SOUTH_BIT = 1 << static_cast<int>(Wall::SOUTH),
    EAST_BIT = 1 << static_cast<int>(Wall::EAST),
};

static const unsigned char WALL_BITS[] = {
    WallBit::NORTH_BIT,
    WallBit::WEST_BIT,
    WallBit::SOUTH_BIT,
    WallBit::EAST_BIT,
};

const static std::array<Wall, WALL_COUNT> OPPOSITE_WALL = {Wall::SOUTH, Wall::EAST, Wall::NORTH, Wall::WEST};

Maze::Maze(Shape shape, Cell start, Cell end) : m_Shape(shape), m_Start(start), m_End(end)
{
    const unsigned char ALL_WALLS = NORTH_BIT | WEST_BIT | SOUTH_BIT | EAST_BIT;
    const size_t CELL_COUNT = m_Shape.height * m_Shape.width;

    m_Cells.reserve(CELL_COUNT);
    std::fill_n(std::back_inserter(m_Cells), CELL_COUNT, ALL_WALLS);
}

Maze::MazeIterator Maze::begin() const
{
    return MazeIterator(m_Shape, {0, 0});
}

Maze::MazeIterator Maze::end() const
{
    return MazeIterator(m_Shape, {0, m_Shape.height});
}

int Maze::RavelCell(Cell cell) const
{
    return cell.x + cell.y * m_Shape.width;
}

const unsigned char &Maze::At(Cell cell) const
{
    return m_Cells[RavelCell(cell)];
}

unsigned char &Maze::At(Cell cell)
{
    return m_Cells[RavelCell(cell)];
}

void Maze::RemoveWall(Cell cell, Wall wall)
{
    _RemoveWall(cell, wall);
    const int wall_index = static_cast<int>(wall);
    _RemoveWall(cell + DIRECTIONS[wall_index], OPPOSITE_WALL[wall_index]);
}

int Maze::Cols() const
{
    return m_Shape.width;
}

int Maze::Rows() const
{
    return m_Shape.height;
}

Cell Maze::StartCell() const
{
    return m_Start;
}

Cell Maze::EndCell() const
{
    return m_End;
}

bool Maze::HasWall(Cell cell, Wall wall) const
{
    return At(cell) & WALL_BITS[static_cast<int>(wall)];
}

bool Maze::OutOfBounds(Cell cell) const
{
    const int width = m_Shape.width;
    const int height = m_Shape.height;
    return cell.x < 0 || cell.x >= width || cell.y < 0 || cell.y >= height;
}

void Maze::_RemoveWall(Cell cell, Wall wall)
{
    if (!OutOfBounds(cell))
    {
        unsigned char &walls = At(cell);
        walls &= ~WALL_BITS[static_cast<int>(wall)];
    }
}

Shape GetCellShape(const Window &window, const Maze &maze)
{
    const auto rect = window.GetActiveArea();
    return {rect.Width() / maze.Cols(), rect.Height() / maze.Rows()};
}

}; // namespace XMaze
