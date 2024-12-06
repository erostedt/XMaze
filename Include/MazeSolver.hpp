#pragma once

#include <vector>

#include "Cell.hpp"
#include "Maze.hpp"

namespace XMaze
{

std::vector<Cell> SolveMaze(const Maze &maze);

};
