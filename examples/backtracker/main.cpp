#include <X11/Xlib.h>
#include <cstdlib>
#include <iostream>

#include "Maze.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

xmaze::Cell RandomCell(xmaze::Shape shape)
{
    xmaze::Cell cell;
    cell.x = rand() % shape.width;
    cell.y = rand() % shape.height;
    return cell;
}

int main()
{
    size_t width = 1280;
    size_t height = 720;
    xmaze::Window window = xmaze::Window::Create(width, height);
    auto pixmap = xmaze::Pixmap(window);

    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    auto screen = window.GetScreen();

    xmaze::Maze maze({4, 3});

    while (!window.ShouldClose())
    {
        auto events = window.GetEvents();
        for (auto &event : events)
        {
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'q')
            {
                window.SetShouldClose();
            }
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'k')
            {
                const auto rect = window.GetActiveArea();
                XSetForeground(display, gc, WhitePixel(display, screen));
                const auto x = rect.top_left.x;
                const auto y = rect.top_left.y;
                const auto w = rect.shape.width;
                const auto h = rect.shape.height;
                XFillRectangle(display, pixmap.GetID(), gc, x, y, w, h);
                XSetForeground(display, gc, BlackPixel(display, screen));
                auto cell = RandomCell(maze.shape);
                maze.RemoveWall(cell, xmaze::WEST);
                xmaze::DrawMaze(maze, window, pixmap);
            }
        }
    }
}
