#include <X11/Xlib.h>

#include "DrawFrame.hpp"
#include "Maze.hpp"
#include "Window.hpp"

namespace xmaze
{

Shape GetCellShape(const Window &window, const Maze &maze)
{
    const auto rect = window.GetActiveArea();
    const auto width = rect.shape.width;
    const auto height = rect.shape.height;

    return {width / maze.Cols(), height / maze.Rows()};
}

}; // namespace xmaze
