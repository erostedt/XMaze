#pragma once

#include <array>

#include <vector>

#include <Pixmap.hpp>
#include <Shape.hpp>
#include <Window.hpp>

namespace xmaze
{

enum WallIndex
{
    NORTH = 0,
    WEST,
    SOUTH,
    EAST,
    COUNT
};

const static std::array<Direction, WallIndex::COUNT> Directions = {Direction{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

class MazeCell
{
  public:
    MazeCell(Origin origin, Shape shape) : m_Origin(origin), m_Shape(shape)
    {
    }

    bool HasWall(WallIndex wall_index) const
    {
        return m_Walls[wall_index];
    }

    void RemoveWall(WallIndex wall_index)
    {
        m_Walls[wall_index] = false;
    }

    Origin GetOrigin() const
    {
        return m_Origin;
    }

    Shape GetShape() const
    {
        return m_Shape;
    }

  private:
    Origin m_Origin;
    Shape m_Shape;
    std::array<bool, WallIndex::COUNT> m_Walls = {true, true, true, true};
};

using Maze = std::vector<MazeCell>;

void DrawMaze(const Maze &maze, const Window &window, Pixmap &pixmap);

} // namespace xmaze
