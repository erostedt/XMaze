#pragma once

template <typename T> struct Point
{
    T x;
    T y;
    Point<T> operator+(const Point<T> &other)
    {
        return {x + other.x, y + other.y};
    }
};
