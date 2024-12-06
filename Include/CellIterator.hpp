#include "Shape.hpp"

namespace xmaze
{

class MazeCellIterator
{
  public:
    using value_type = Cell;

    MazeCellIterator(Shape shape, Cell start) : m_Shape(shape), m_CurrentCol(start.x), m_CurrentRow(start.y)
    {
    }

    // Dereference operator
    value_type operator*() const
    {
        return {m_CurrentCol, m_CurrentRow};
    }

    MazeCellIterator &operator++()
    {
        ++m_CurrentCol;
        if (m_CurrentCol == m_Shape.width)
        {
            m_CurrentCol = 0;
            ++m_CurrentRow;
        }
        return *this;
    }

    MazeCellIterator operator++(int)
    {
        MazeCellIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const MazeCellIterator &other) const
    {
        return m_CurrentRow == other.m_CurrentRow && m_CurrentCol == other.m_CurrentCol;
    }

    bool operator!=(const MazeCellIterator &other) const
    {
        return !(*this == other);
    }

  private:
    Shape m_Shape;
    int m_CurrentCol;
    int m_CurrentRow;
};

}; // namespace xmaze
