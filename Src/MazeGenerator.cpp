#include <random>
#include <stack>
#include <unordered_set>

#include "MazeGenerator.hpp"
#include "Shape.hpp"

namespace XMaze
{

static std::random_device rd;
static std::mt19937 gen(rd());

Wall RandomWall(const std::vector<Wall> &walls)
{
    std::uniform_int_distribution<> dis(0, walls.size() - 1);
    return walls[dis(gen)];
}

MazeGenerator::MazeGenerator(Shape shape, Cell start, Cell end) : m_Maze(shape, start, end), m_Current(start)
{
    m_CellStack.push(m_Current);
    m_CurrentWalls.reserve(WALL_COUNT);
}

MazeGenerator::MazeGenerator(Shape shape)
    : MazeGenerator(shape, {0, 0}, {static_cast<int>(shape.width) - 1, static_cast<int>(shape.height) - 1})
{
}

bool MazeGenerator::IsDone() const
{
    return m_CellStack.empty();
}

Cell MazeGenerator::CurrentCell() const
{
    return m_Current;
}

bool MazeGenerator::Advance()
{
    if (IsDone())
    {
        return true;
    }

    m_Visited.insert(m_Maze.RavelCell(m_Current));

    m_CurrentWalls.clear();
    for (const auto wall : WALLS)
    {
        Cell neighbor = m_Current + DIRECTIONS[wall];
        if (!m_Visited.contains(m_Maze.RavelCell(neighbor)) && !m_Maze.OutOfBounds(neighbor))
        {
            m_CurrentWalls.push_back(wall);
        }
    }

    if (m_CurrentWalls.empty())
    {
        m_Current = m_CellStack.top();
        m_CellStack.pop();
        return IsDone();
    }

    Wall wall = RandomWall(m_CurrentWalls);
    m_Maze.RemoveWall(m_Current, wall);

    m_Current = m_Current + DIRECTIONS[wall];
    m_CellStack.push(m_Current);
    return false;
}

const Maze &MazeGenerator::GetMaze() const
{
    return m_Maze;
}

Maze MazeGenerator::Generate()
{
    while (!IsDone())
    {
        Advance();
    }
    return m_Maze;
}

} // namespace XMaze
