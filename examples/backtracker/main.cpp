#include <X11/Xlib.h>

#include "Maze.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

int main()
{
    size_t width = 800;
    size_t height = 600;
    xmaze::Window window = xmaze::Window::Create(width, height);
    auto pixmap = xmaze::Pixmap(window);

    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    auto screen = window.GetScreen();
    XSetForeground(display, gc, WhitePixel(display, screen));
    XFillRectangle(display, pixmap.GetID(), gc, 0, 0, 800, 600);
    XSetForeground(display, gc, BlackPixel(display, screen));

    xmaze::Maze maze = {
        {{0, 0}, {100, 200}},
        {{200, 200}, {100, 200}},
    };

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
                xmaze::DrawMaze(maze, window, pixmap);
            }
        }
    }
}
