#include "Draw.hpp"
#include "Maze.hpp"

#include <stdexcept>

namespace XMaze
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
    auto pixmap = window.GetPixmap();
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    SetPenColor(display, window.GetScreen(), gc, color);
    const auto [ix, iy] = cell;
    const auto [cw, ch] = cell_shape;
    XFillRectangle(display, pixmap, gc, ix * cw, iy * ch, cw, ch);
}

void DrawMaze(const Maze &maze, DrawFrame &draw_frame)
{
    const auto &window = draw_frame.GetWindow();
    auto pixmap = window.GetPixmap();
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    SetDefaultPen(display, gc);

    const auto [cell_width, cell_height] = GetCellShape(window, maze);

    SetPenColor(display, window.GetScreen(), gc, "black");
    for (const auto cell : maze)
    {
        const auto [ix, iy] = cell;
        const short xstart = ix * cell_width;
        const short xend = (ix + 1) * cell_width;
        const short ystart = iy * cell_height;
        const short yend = (iy + 1) * cell_height;
        if (maze.HasWall({ix, iy}, Wall::NORTH))
        {
            XDrawLine(display, pixmap, gc, xstart, ystart, xend, ystart);
        }
        if (maze.HasWall({ix, iy}, Wall::WEST))
        {
            XDrawLine(display, pixmap, gc, xstart, ystart, xstart, yend);
        }
        if (maze.HasWall({ix, iy}, Wall::SOUTH))
        {
            XDrawLine(display, pixmap, gc, xstart, yend, xend, yend);
        }
        if (maze.HasWall({ix, iy}, Wall::EAST))
        {
            XDrawLine(display, pixmap, gc, xend, ystart, xend, yend);
        }
    }
}

}; // namespace XMaze
