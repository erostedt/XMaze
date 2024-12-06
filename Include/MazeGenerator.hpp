#pragma once

#include <stack>
#include <unordered_set>

#include "Cell.hpp"
#include "Maze.hpp"
#include "Shape.hpp"

namespace XMaze
{

class MazeGenerator
{
  public:
    MazeGenerator(Shape shape, Cell start, Cell end);
    MazeGenerator(Shape shape);
    const Maze &GetMaze() const;
    bool IsDone() const;
    Cell CurrentCell() const;
    bool Advance();
    Maze Generate();

  private:
    Maze m_Maze;
    Cell m_Current;
    std::stack<Cell> m_CellStack;
    std::unordered_set<int> m_Visited;
    std::vector<Wall> m_CurrentWalls;
};

} // namespace XMaze
