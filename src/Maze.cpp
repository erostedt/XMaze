#include "Maze.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

namespace xmaze
{

void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap)
{
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    const auto [width, height] = window.GetShape();

    for (const auto &cell : maze)
    {
        const auto origin = cell.GetOrigin();
        const auto shape = cell.GetShape();

        if (cell.HasWall(NORTH))
        {
            const auto xstart = origin.X;
            const auto xend = origin.X + shape.Width;
            const auto y = origin.Y;
            XDrawLine(display, pixmap.GetID(), gc, xstart, y, xend, y);
        }
        if (cell.HasWall(WEST))
        {
            const auto x = origin.X;
            const auto ystart = origin.Y;
            const auto yend = origin.Y + shape.Height;
            XDrawLine(display, pixmap.GetID(), gc, x, ystart, x, yend);
        }
        if (cell.HasWall(SOUTH))
        {
            const auto xstart = origin.X;
            const auto xend = origin.X + shape.Width;
            const auto y = origin.Y + shape.Height;
            XDrawLine(display, pixmap.GetID(), gc, xstart, y, xend, y);
        }
        if (cell.HasWall(EAST))
        {
            const auto x = origin.X + shape.Width;
            const auto ystart = origin.Y;
            const auto yend = origin.Y + shape.Height;
            XDrawLine(display, pixmap.GetID(), gc, x, ystart, x, yend);
        }
    }

    XFlush(display);
    XCopyArea(display, pixmap.GetID(), window.GetNativeWindow(), gc, 0, 0, width, height, 0, 0);
}

}; // namespace xmaze
