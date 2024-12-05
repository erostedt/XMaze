#include <X11/Xlib.h>
#include <cstdlib>

#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

int main()
{
    size_t width = 1280;
    size_t height = 720;
    xmaze::Window window = xmaze::Window::Create(width, height);
    auto pixmap = xmaze::Pixmap(window);

    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    auto screen = window.GetScreen();

    xmaze::MazeGenerator generator({40, 30});

    while (!window.ShouldClose())
    {
        auto events = window.GetEvents();
        for (auto &event : events)
        {
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'q')
            {
                window.SetShouldClose();
            }
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'u')
            {
                const auto rect = window.GetActiveArea();
                XSetForeground(display, gc, WhitePixel(display, screen));
                XFillRectangle(display, pixmap.GetID(), gc, rect.Left(), rect.Top(), rect.Width(), rect.Height());
                XSetForeground(display, gc, BlackPixel(display, screen));
                generator.Advance();
                const auto &maze = generator.GetMaze();
                const auto cell_shape = xmaze::GetCellShape(window, maze);
                DrawCell(maze.StartCell(), cell_shape, "red", window, pixmap);
                DrawCell(maze.EndCell(), cell_shape, "green", window, pixmap);
                DrawCell(generator.CurrentCell(), cell_shape, "blue", window, pixmap);
                xmaze::DrawMaze(generator.GetMaze(), window, pixmap);

                XFlush(display);
                XCopyArea(display, pixmap.GetID(), window.GetNativeWindow(), gc, 0, 0, width, height, 0, 0);
            }
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'g')
            {
                const auto rect = window.GetActiveArea();
                XSetForeground(display, gc, WhitePixel(display, screen));
                XFillRectangle(display, pixmap.GetID(), gc, rect.Left(), rect.Top(), rect.Width(), rect.Height());
                XSetForeground(display, gc, BlackPixel(display, screen));
                generator.Generate();
                const auto &maze = generator.GetMaze();
                const auto cell_shape = xmaze::GetCellShape(window, maze);
                DrawCell(maze.StartCell(), cell_shape, "red", window, pixmap);
                DrawCell(maze.EndCell(), cell_shape, "green", window, pixmap);
                xmaze::DrawMaze(generator.GetMaze(), window, pixmap);

                XFlush(display);
                XCopyArea(display, pixmap.GetID(), window.GetNativeWindow(), gc, 0, 0, width, height, 0, 0);
            }
        }
    }
}
