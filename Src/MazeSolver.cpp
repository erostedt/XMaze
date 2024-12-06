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

bool MazeSolver::IsSolved() const
{
    const auto current_cell = CurrentCell();
    return current_cell && (current_cell->Position == m_Maze.EndCell());
}

bool MazeSolver::HasTerminated() const
{
    return m_Queue.empty() || IsSolved();
}

std::optional<AStarCell> MazeSolver::CurrentCell() const
{
    if (m_Queue.empty())
    {
        return {};
    }
    return m_Queue.top();
}

std::optional<Path> MazeSolver::GetPath() const
{
    const auto current = CurrentCell();
    if (!current)
    {
        return {};
    }

    const auto start = m_Maze.StartCell();
    std::vector<Cell> path;
    Cell curr = current->Position;
    while (curr != start)
    {
        path.push_back(curr);
        curr = m_Parents.at(curr);
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

bool MazeSolver::Advance()
{
    if (HasTerminated())
    {
        return true;
    }

    const auto end = m_Maze.EndCell();

    auto current = m_Queue.top();
    m_Queue.pop();

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
