#include "MazeSolver.hpp"

#include <algorithm>
#include <math.h>
#include <queue>
#include <unordered_map>

#include "Cell.hpp"

namespace XMaze
{

int ManhattanHeuristic(Cell current_cell, Cell target_cell)
{
    return std::abs(current_cell.x - target_cell.x) + std::abs(current_cell.y - target_cell.y);
}

MazeSolver::MazeSolver(const Maze &maze) : m_Maze(maze)
{
    const auto start = m_Maze.StartCell();
    const auto end = m_Maze.EndCell();
    m_Queue.push({start, ManhattanHeuristic(start, end)});
    m_MinDistancesTraveled[start] = 0;
}

bool MazeSolver::HasTerminated() const
{
    return m_Queue.empty() || m_Path.has_value();
}

std::optional<Path> MazeSolver::GetPath() const
{
    return m_Path;
}

bool MazeSolver::Advance()
{
    if (HasTerminated())
    {
        return true;
    }

    const auto start = m_Maze.StartCell();
    const auto end = m_Maze.EndCell();

    auto current = m_Queue.top();
    m_Queue.pop();

    if (current.Position == end)
    {
        std::vector<Cell> path;
        Cell curr = current.Position;
        while (curr != start)
        {
            path.push_back(curr);
            curr = m_Parents[curr];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        m_Path = path;
        return true;
    }

    for (const auto wall : WALLS)
    {
        if (m_Maze.HasWall(current.Position, wall))
        {
            continue;
        }

        Cell neighbor = current.Position + GetDirection(wall);
        int tentative_distance_traveled = m_MinDistancesTraveled[current.Position] + 1;

        const auto min_distance_traveled = m_MinDistancesTraveled.find(neighbor);
        if (min_distance_traveled != m_MinDistancesTraveled.cend() &&
            min_distance_traveled->second < tentative_distance_traveled)
        {
            continue;
        }

        m_MinDistancesTraveled[neighbor] = tentative_distance_traveled;

        m_Parents[neighbor] = current.Position;
        m_Queue.push({neighbor, tentative_distance_traveled + ManhattanHeuristic(neighbor, end)});
    }

    return HasTerminated();
}

std::optional<Path> MazeSolver::Solve()
{
    while (!HasTerminated())
    {
        Advance();
    }
    return GetPath();
}

}; // namespace XMaze
