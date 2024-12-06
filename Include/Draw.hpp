#pragma once

#include "DrawFrame.hpp"
#include "Maze.hpp"
#include "Shape.hpp"

namespace xmaze
{

void DrawCell(Cell cell, Shape cell_shape, const char *color, DrawFrame &draw_frame);
void DrawMaze(const Maze &maze, DrawFrame &draw_frame);

} // namespace xmaze
