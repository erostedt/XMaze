#include "Draw.hpp"
#include "DrawFrame.hpp"
#include "LimitFps.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "MazeSolver.hpp"
#include "Window.hpp"
#include <iostream>

using namespace XMaze;

void DrawPath(const Maze &maze, const MazeSolver &solver, DrawFrame &frame)
{
    const auto path = solver.GetPath();
    if (!path)
    {
        std::cout << "Failed" << std::endl;
        return;
    }

    const char *solved_color = "green";
    const char *searching_color = "blue";

    const char *color = solver.IsSolved() ? solved_color : searching_color;
    const auto cell_shape = GetCellShape(frame.GetWindow(), maze);
    for (const auto cell : *path)
    {
        DrawCell(cell, cell_shape, color, frame);
    }
    DrawMaze(maze, frame);
}

int main()
{
    const size_t WIDTH = 1920;
    const size_t HEIGHT = 1080;
    const size_t MAZE_COLS = 16 * 5;
    const size_t MAZE_ROWS = 9 * 5;
    const size_t FPS = 60;

    XMaze::Window window = XMaze::Window::Create(WIDTH, HEIGHT);

    MazeGenerator generator({MAZE_COLS, MAZE_ROWS});
    const auto maze = generator.Generate();
    MazeSolver solver(maze);

    while (!window.ShouldClose())
    {
        LimitFps fps(FPS);
        auto events = window.GetEvents();
        for (auto &event : events)
        {
            if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 'q')
            {
                window.SetShouldClose();
            }
            else if (event.type == KeyPress && XLookupKeysym(&event.xkey, 0) == 's')
            {
                solver.Solve();
            }
        }

        solver.Advance();
        DrawFrame frame = window.NewDrawFrame();
        DrawPath(maze, solver, frame);
    }
}
