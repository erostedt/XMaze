#include "Maze.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

namespace xmaze
{

void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap)
{
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    const auto rect = window.GetActiveArea();

    const auto width = rect.shape.width;
    const auto height = rect.shape.height;

    const size_t cell_width = width / maze.shape.width;
    const size_t cell_height = height / maze.shape.height;

    for (size_t iy = 0; iy < maze.shape.height; ++iy)
    {
        for (size_t ix = 0; ix < maze.shape.width; ++ix)
        {
            const auto cell = maze.At(ix, iy);

            const auto xstart = ix * cell_width;
            const auto xend = (ix + 1) * cell_width;
            const auto ystart = iy * cell_height;
            const auto yend = (iy + 1) * cell_height;
            if (cell & NORTH_BIT)
            {
                XDrawLine(display, pixmap.GetID(), gc, xstart, ystart, xend, ystart);
            }
            if (cell & WEST_BIT)
            {
                XDrawLine(display, pixmap.GetID(), gc, xstart, ystart, xstart, yend);
            }
            if (cell & SOUTH_BIT)
            {
                XDrawLine(display, pixmap.GetID(), gc, xstart, yend, xend, yend);
            }
            if (cell & EAST_BIT)
            {
                XDrawLine(display, pixmap.GetID(), gc, xend, ystart, xend, yend);
            }
        }
    }

    XFlush(display);
    const auto x = rect.top_left.x;
    const auto y = rect.top_left.y;
    XCopyArea(display, pixmap.GetID(), window.GetNativeWindow(), gc, 0, 0, width, height, x, y);
}

}; // namespace xmaze
