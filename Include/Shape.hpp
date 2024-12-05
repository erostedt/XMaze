#pragma once

#include <cstddef>

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
using Origin = Point<size_t>;

struct Shape
{
    size_t width;
    size_t height;
};

struct Rect
{
    Origin top_left;
    Shape shape;

    size_t Left() const
    {
        return top_left.x;
    }
    size_t Right() const
    {
        return top_left.x + shape.width;
    }
    size_t Top() const
    {
        return top_left.y;
    }
    size_t Bottom() const
    {
        return top_left.y + shape.height;
    }
    size_t Width() const
    {
        return shape.width;
    }
    size_t Height() const
    {
        return shape.height;
    }
};

}; // namespace xmaze
