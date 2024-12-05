#include <stdexcept>

#include <X11/Xlib.h>

#include "DrawFrame.hpp"
#include "Maze.hpp"
#include "Pixmap.hpp"
#include "Window.hpp"

namespace xmaze
{

void SetDefaultPen(Display *display, GC gc)
{
    XSetLineAttributes(display, gc, 5, LineSolid, CapRound, JoinRound);
}

void SetPenColor(Display *display, int screen, GC gc, const char *color)
{
    XColor x_color;
    Colormap colormap = DefaultColormap(display, screen);

    if (!XParseColor(display, colormap, color, &x_color))
    {
        throw std::runtime_error("Invalid color");
    }

    if (!XAllocColor(display, colormap, &x_color))
    {
        throw std::runtime_error("Invalid color");
    }

    XSetForeground(display, gc, x_color.pixel);
}

void DrawCell(Cell cell, Shape cell_shape, const char *color, DrawFrame &draw_frame)
{
    const auto &window = draw_frame.GetWindow();
    auto &pixmap = draw_frame.GetPixmap();
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    SetPenColor(display, window.GetScreen(), gc, color);
    const auto [ix, iy] = cell;
    const auto [cw, ch] = cell_shape;
    XFillRectangle(display, pixmap.GetID(), gc, ix * cw, iy * ch, cw, ch);
}

void DrawMaze(const Maze &maze, DrawFrame &draw_frame)
{
    const auto &window = draw_frame.GetWindow();
    auto &pixmap = draw_frame.GetPixmap();
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    SetDefaultPen(display, gc);

    const auto rect = window.GetActiveArea();
    const auto width = rect.shape.width;
    const auto height = rect.shape.height;

    const size_t cell_width = width / maze.Cols();
    const size_t cell_height = height / maze.Rows();

    SetPenColor(display, window.GetScreen(), gc, "black");
    for (size_t iy = 0; iy < maze.Rows(); ++iy)
    {
        for (size_t ix = 0; ix < maze.Cols(); ++ix)
        {
            const auto cell = maze.At(ix, iy);

            const short xstart = ix * cell_width;
            const short xend = (ix + 1) * cell_width;
            const short ystart = iy * cell_height;
            const short yend = (iy + 1) * cell_height;
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
}

Shape GetCellShape(const Window &window, const Maze &maze)
{
    const auto rect = window.GetActiveArea();
    const auto width = rect.shape.width;
    const auto height = rect.shape.height;

    return {width / maze.Cols(), height / maze.Rows()};
}

}; // namespace xmaze
