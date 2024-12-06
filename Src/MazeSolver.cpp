#include "MazeSolver.hpp"
#include "Cell.hpp"

#include <functional>
#include <iostream>
#include <limits>
#include <math.h>
#include <queue>
#include <stdexcept>
#include <unordered_map>

namespace XMaze
{

const int DEFAULT_FSCORE = std::numeric_limits<int>::max();

struct AStarCell
{
    Cell Position;
    int FScore = DEFAULT_FSCORE;

    bool operator>(const AStarCell &other) const
    {
        return FScore > other.FScore;
    }
};

int ManhattanHeuristic(Cell current_cell, Cell target_cell)
{
    return std::abs(current_cell.x - target_cell.x) + std::abs(current_cell.y - target_cell.y);
}

std::vector<Cell> SolveMaze(const Maze &maze)
{
    std::priority_queue<AStarCell, std::vector<AStarCell>, std::greater<AStarCell>> queue;
    Cell start_cell = maze.StartCell();
    Cell end_cell = maze.EndCell();
    queue.push({start_cell, ManhattanHeuristic(start_cell, end_cell)});

    std::vector<Cell> neighbors;
    neighbors.reserve(WALL_COUNT);
    std::unordered_map<Cell, int> min_distances_traveled = {{start_cell, 0}};
    std::unordered_map<Cell, Cell> parents;

    while (!queue.empty())
    {
        auto current = queue.top();
        queue.pop();

        if (current.Position == end_cell)
        {
            std::cout << "Found path!" << std::endl;

            std::vector<Cell> path;
            Cell curr = current.Position;
            while (curr != start_cell)
            {
                path.push_back(curr);
                curr = parents[curr];
            }
            path.push_back(start_cell);
            std::reverse(path.begin(), path.end());
            return path;
        }

        neighbors.clear();
        for (const auto wall : WALLS)
        {
            if (maze.HasWall(current.Position, wall))
            {
                continue;
            }

            Cell neighbor = current.Position + GetDirection(wall);
            if (!min_distances_traveled.contains(neighbor))
            {
                min_distances_traveled[neighbor] = DEFAULT_FSCORE;
            }

            int tentative_distance_traveled = min_distances_traveled[current.Position] + 1;
            if (tentative_distance_traveled >= min_distances_traveled[neighbor])
            {
                continue;
            }

            min_distances_traveled[neighbor] = tentative_distance_traveled;

            parents[neighbor] = current.Position;
            queue.push({neighbor, tentative_distance_traveled + ManhattanHeuristic(neighbor, end_cell)});
        }
    }

    throw std::runtime_error("Maze does not contain a solution!");
}

}; // namespace XMaze
