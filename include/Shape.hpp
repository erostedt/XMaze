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
};

}; // namespace xmaze
