#pragma once

namespace xmaze
{

template <typename T> struct Point
{
    T x;
    T y;
    Point<T> operator+(const Point<T> &other)
    {
        return {x + other.x, y + other.y};
    }
};

using Cell = Point<int>;
using Direction = Point<int>;
using Origin = Point<int>;

struct Shape
{
    int width;
    int height;
};

struct Rect
{
    Origin top_left;
    Shape shape;

    int Left() const
    {
        return top_left.x;
    }
    int Right() const
    {
        return top_left.x + shape.width;
    }
    int Top() const
    {
        return top_left.y;
    }
    int Bottom() const
    {
        return top_left.y + shape.height;
    }
    int Width() const
    {
        return shape.width;
    }
    int Height() const
    {
        return shape.height;
    }
};

}; // namespace xmaze
