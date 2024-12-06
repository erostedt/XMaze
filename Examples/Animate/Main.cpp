#include <X11/Xlib.h>
#include <chrono>
#include <cstdlib>
#include <thread>

#include "Draw.hpp"
#include "DrawFrame.hpp"
#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include "Window.hpp"

class LimitFps
{
  public:
    LimitFps(size_t max_fps) : m_MinElapsedTime(1'000'000'000 / max_fps)
    {
        m_Start = std::chrono::high_resolution_clock::now();
    }
    ~LimitFps()
    {
        const auto end = std::chrono::high_resolution_clock::now();
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_Start);
        if (elapsed < m_MinElapsedTime)
        {
            std::this_thread::sleep_for(m_MinElapsedTime - elapsed);
        }
    }

  private:
    std::chrono::nanoseconds m_MinElapsedTime;
    std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds> m_Start;
};

int main()
{
    const size_t WIDTH = 1920;
    const size_t HEIGHT = 1080;
    const size_t MAZE_COLS = 16 * 3;
    const size_t MAZE_ROWS = 9 * 3;
    const size_t FPS = 60;

    xmaze::Window window = xmaze::Window::Create(WIDTH, HEIGHT);

    xmaze::MazeGenerator generator({MAZE_COLS, MAZE_ROWS});

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
        xmaze::DrawFrame frame(window);
        generator.Advance();
        const auto &maze = generator.GetMaze();
        const auto cell_shape = xmaze::GetCellShape(window, maze);
        DrawCell(maze.StartCell(), cell_shape, "red", frame);
        DrawCell(maze.EndCell(), cell_shape, "green", frame);
        DrawCell(generator.CurrentCell(), cell_shape, "blue", frame);
        DrawMaze(generator.GetMaze(), frame);
    }
}
