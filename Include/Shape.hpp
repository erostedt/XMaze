#pragma once

#include "Point.hpp"

namespace XMaze
{

using TopLeft = Point<int>;

struct Shape
{
    int width;
    int height;
};

class Rect
{
  public:
    Rect(TopLeft top_left, Shape shape) : m_TopLeft(top_left), m_Shape(shape)
    {
    }

    int Left() const
    {
        return m_TopLeft.x;
    }

    int Right() const
    {
        return m_TopLeft.x + m_Shape.width;
    }

    int Top() const
    {
        return m_TopLeft.y;
    }

    int Bottom() const
    {
        return m_TopLeft.y + m_Shape.height;
    }

    int Width() const
    {
        return m_Shape.width;
    }

    int Height() const
    {
        return m_Shape.height;
    }

    int Area() const
    {
        return Width() * Height();
    }

  private:
    TopLeft m_TopLeft;
    Shape m_Shape;
};

}; // namespace XMaze
