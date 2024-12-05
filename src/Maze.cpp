#include <random>
#include <stack>
#include <stdexcept>
#include <unordered_set>

#include <X11/Xlib.h>

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

void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap)
{
    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    SetDefaultPen(display, gc);

    const auto rect = window.GetActiveArea();
    const auto width = rect.shape.width;
    const auto height = rect.shape.height;

    const size_t cell_width = width / maze.Cols();
    const size_t cell_height = height / maze.Rows();

    SetPenColor(display, window.GetScreen(), gc, "red");
    const auto [start_x, start_y] = maze.StartCell();
    XFillRectangle(display, pixmap.GetID(), gc, start_x * cell_width, start_y * cell_height, cell_width, cell_height);

    SetPenColor(display, window.GetScreen(), gc, "green");
    const auto [end_x, end_y] = maze.EndCell();
    XFillRectangle(display, pixmap.GetID(), gc, end_x * cell_width, end_y * cell_height, cell_width, cell_height);

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

    XFlush(display);
    XCopyArea(display, pixmap.GetID(), window.GetNativeWindow(), gc, 0, 0, width, height, 0, 0);
}

static std::random_device rd;
static std::mt19937 gen(rd());

Wall RandomWall(const std::vector<Wall> &walls)
{
    std::uniform_int_distribution<> dis(0, walls.size() - 1);
    return walls[dis(gen)];
}

Maze GenerateMaze(Shape shape)
{
    const int end_x = static_cast<int>(shape.width) - 1;
    const int end_y = static_cast<int>(shape.height) - 1;
    return GenerateMaze(shape, {0, 0}, {end_x, end_y});
}

Maze GenerateMaze(Shape shape, Cell start, Cell end)
{
    Maze maze(shape, start, end);

    std::stack<Cell> cells;
    Cell current = {0, 0};
    cells.push(current);
    std::unordered_set<int> visited;
    std::vector<Wall> walls;
    walls.reserve(WALL_COUNT);

    while (!cells.empty())
    {
        visited.insert(maze.RavelCell(current));

        walls.clear();
        for (const auto wall : WALLS)
        {
            Cell neighbor = current + DIRECTIONS[wall];
            if (!visited.contains(maze.RavelCell(neighbor)) && !maze.OutOfBounds(neighbor))
            {
                walls.push_back(wall);
            }
        }

        if (walls.empty())
        {
            current = cells.top();
            cells.pop();
            continue;
        }

        Wall wall = RandomWall(walls);
        maze.RemoveWall(current, wall);

        current = current + DIRECTIONS[wall];
        cells.push(current);
    }

    return maze;
}
}; // namespace xmaze
