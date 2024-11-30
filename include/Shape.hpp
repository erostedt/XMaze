#pragma once

#include <cstddef>

template <typename T> struct Point
{
    T X;
    T Y;
};

using Origin = Point<size_t>;
using Direction = Point<int>;

struct Shape
{
    size_t Width;
    size_t Height;
};
