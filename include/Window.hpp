#pragma once
#include <X11/Xlib.h>
#include <vector>

#include <Shape.hpp>

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
    Shape GetShape() const;
    size_t GetWidth() const;
    size_t GetHeight() const;
    Display *GetDisplay() const;
    int GetScreen() const;
    ::Window GetNativeWindow() const;
    GC GetGC() const;
    ~Window();

  private:
    Display *m_Display;
    int m_Screen;
    ::Window m_Window;
    GC m_GC;
    bool m_ShouldClose = false;
};

}; // namespace xmaze
