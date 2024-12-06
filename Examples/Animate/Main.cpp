#include "Draw.hpp"
#include "DrawFrame.hpp"
#include "LimitFps.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Window.hpp"

using namespace XMaze;

int main()
{
    const size_t WIDTH = 1920;
    const size_t HEIGHT = 1080;
    const size_t MAZE_COLS = 16 * 3;
    const size_t MAZE_ROWS = 9 * 3;
    const size_t FPS = 60;

    XMaze::Window window = XMaze::Window::Create(WIDTH, HEIGHT);

    MazeGenerator generator({MAZE_COLS, MAZE_ROWS});

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
        }

        DrawFrame frame = window.NewDrawFrame();
        generator.Advance();
        const auto &maze = generator.GetMaze();
        const auto cell_shape = GetCellShape(window, maze);
        DrawCell(maze.StartCell(), cell_shape, "red", frame);
        DrawCell(maze.EndCell(), cell_shape, "green", frame);
        DrawCell(generator.CurrentCell(), cell_shape, "blue", frame);
        DrawMaze(generator.GetMaze(), frame);
    }
}
