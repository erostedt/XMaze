#pragma once
#include <X11/Xlib.h>
#include <vector>

namespace xmaze
{

class Window
{
  public:
    static Window Create(size_t width, size_t height);
    void Draw();
    bool ShouldClose();
    void SetShouldClose();
    std::vector<XEvent> GetEvents();
    XImage *Image();
    ~Window();

  private:
    Display *m_Display;
    int m_Screen;
    ::Window m_Window;
    GC m_GC;
    size_t m_Width;
    size_t m_Height;
    XImage *m_BackBuffer;
    bool m_ShouldClose = false;
};

}; // namespace xmaze
