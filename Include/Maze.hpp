#pragma once

#include <vector>

#include "Cell.hpp"
#include "DrawFrame.hpp"
#include "Shape.hpp"
#include "Window.hpp"

namespace XMaze
{

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

    int Rows() const;
    int Cols() const;
    bool OutOfBounds(Cell cell) const;

    const unsigned char &At(Cell cell) const;
    unsigned char &At(Cell cell);

    bool HasWall(Cell cell, Wall wall) const;
    void RemoveWall(Cell cell, Wall wall);

    Cell StartCell() const;
    Cell EndCell() const;

  private:
    int RavelCell(Cell cell) const;
    void _RemoveWall(Cell cell, Wall wall);

  public:
    Shape m_Shape;
    Cell m_Start;
    Cell m_End;
    std::vector<unsigned char> m_Cells;
};

Shape GetCellShape(const Window &window, const Maze &maze);

} // namespace XMaze
