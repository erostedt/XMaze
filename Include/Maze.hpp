#pragma once

#include <array>
#include <vector>

#include "Cell.hpp"
#include "DrawFrame.hpp"
#include "Shape.hpp"
#include "Window.hpp"

namespace XMaze
{

static const size_t WALL_COUNT = 4;

enum class Wall
{
    NORTH = 0,
    WEST,
    SOUTH,
    EAST
};

const static std::array<Wall, WALL_COUNT> WALLS = {Wall::NORTH, Wall::WEST, Wall::SOUTH, Wall::EAST};

Direction GetDirection(Wall wall);

class Maze
{

  public:
    class MazeIterator
    {
      public:
        using value_type = Cell;

        MazeIterator(Shape shape, Cell start) : m_Shape(shape), m_CurrentCol(start.x), m_CurrentRow(start.y)
        {
        }

        // Dereference operator
        value_type operator*() const
        {
            return {m_CurrentCol, m_CurrentRow};
        }

        MazeIterator &operator++()
        {
            ++m_CurrentCol;
            if (m_CurrentCol == m_Shape.width)
            {
                m_CurrentCol = 0;
                ++m_CurrentRow;
            }
            return *this;
        }

        MazeIterator operator++(int)
        {
            MazeIterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const MazeIterator &other) const
        {
            return m_CurrentRow == other.m_CurrentRow && m_CurrentCol == other.m_CurrentCol;
        }

        bool operator!=(const MazeIterator &other) const
        {
            return !(*this == other);
        }

      private:
        Shape m_Shape;
        int m_CurrentCol;
        int m_CurrentRow;
    };

  public:
    Maze(Shape shape, Cell start, Cell end);

    MazeIterator begin() const;
    MazeIterator end() const;

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

} // namespace XMaze
