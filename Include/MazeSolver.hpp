#pragma once

#include <optional>
#include <queue>
#include <vector>

#include "Cell.hpp"
#include "Maze.hpp"

namespace XMaze
{

using Path = std::vector<Cell>;

struct AStarCell
{
    Cell Position;
    int FScore;

    bool operator>(const AStarCell &other) const
    {
        return FScore > other.FScore;
    }
};

class MazeSolver
{
  public:
    MazeSolver(const Maze &maze);

    std::optional<Path> GetPath() const;
    bool HasTerminated() const;

    bool Advance();
    std::optional<Path> Solve();

  private:
    const Maze &m_Maze;
    std::priority_queue<AStarCell, std::vector<AStarCell>, std::greater<AStarCell>> m_Queue;
    std::unordered_map<Cell, int> m_MinDistancesTraveled;
    std::unordered_map<Cell, Cell> m_Parents;
    std::optional<Path> m_Path;
};

}; // namespace XMaze
