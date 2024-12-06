#pragma once

namespace xmaze
{
class Window;

class DrawFrame
{
  public:
    DrawFrame(xmaze::Window &window);
    ~DrawFrame();
    const xmaze::Window &GetWindow() const;

  private:
    xmaze::Window &m_Window;
};
}; // namespace xmaze
