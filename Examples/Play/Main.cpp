#include "Cell.hpp"
#include "Draw.hpp"
#include "DrawFrame.hpp"
#include "LimitFps.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Window.hpp"
#include <unordered_set>

using namespace XMaze;

void DrawVisitedCells(const Maze &maze, const std::unordered_set<Cell> &visited, const char *color, DrawFrame &frame)
{
    const auto cell_shape = GetCellShape(frame.GetWindow(), maze);
    for (const auto cell : visited)
    {
        DrawCell(cell, cell_shape, color, frame);
    }
}

static bool PressedKey(_XEvent event, unsigned long key)
{
    return event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == key;
}

static Cell TryMove(Cell current_cell, Wall wall, const Maze &maze)
{
    Cell next_cell = current_cell + GetDirection(wall);
    bool is_invalid_move = maze.HasWall(current_cell, wall) || maze.OutOfBounds(next_cell);
    return (is_invalid_move) ? current_cell : next_cell;
}

int main()
{
    const size_t WIDTH = 1920;
    const size_t HEIGHT = 1080;
    const size_t MAZE_COLS = 16 * 3;
    const size_t MAZE_ROWS = 9 * 3;
    const size_t FPS = 120;
    const char *VISITED_COLOR = "blue";
    const char *CURRENT_COLOR = "magenta";
    const char *END_COLOR = "green";

    XMaze::Window window = XMaze::Window::Create(WIDTH, HEIGHT);

    MazeGenerator generator({MAZE_COLS, MAZE_ROWS});
    const auto maze = generator.Generate();
    Cell current_cell = maze.StartCell();
    Cell end_cell = maze.EndCell();
    std::unordered_set<Cell> visited = {current_cell};

    while (!window.ShouldClose())
    {
        LimitFps fps(FPS);
        auto events = window.GetEvents();
        for (auto &event : events)
        {
            if (PressedKey(event, 'q'))
            {
                window.SetShouldClose();
            }

            else if (current_cell == end_cell)
            {
                continue;
            }

            else if (PressedKey(event, 'w'))
            {
                current_cell = TryMove(current_cell, Wall::NORTH, maze);
                visited.insert(current_cell);
            }

            else if (PressedKey(event, 's'))
            {
                current_cell = TryMove(current_cell, Wall::SOUTH, maze);
                visited.insert(current_cell);
            }

            else if (PressedKey(event, 'a'))
            {
                current_cell = TryMove(current_cell, Wall::WEST, maze);
                visited.insert(current_cell);
            }

            else if (PressedKey(event, 'd'))
            {
                current_cell = TryMove(current_cell, Wall::EAST, maze);
                visited.insert(current_cell);
            }
        }

        DrawFrame frame = window.NewDrawFrame();
        const auto cell_shape = GetCellShape(frame.GetWindow(), maze);

        DrawVisitedCells(maze, visited, VISITED_COLOR, frame);
        DrawCell(maze.EndCell(), cell_shape, END_COLOR, frame);
        DrawCell(current_cell, cell_shape, CURRENT_COLOR, frame);

        DrawMaze(maze, frame);
    }
}
