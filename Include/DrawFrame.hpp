#pragma once

namespace XMaze
{
class Window;

class DrawFrame
{
  public:
    DrawFrame(Window &window);
    ~DrawFrame();
    const Window &GetWindow() const;

  private:
    Window &m_Window;
};
}; // namespace XMaze
