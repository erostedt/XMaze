#pragma once
#include <X11/Xlib.h>
#include <vector>

namespace xmaze
{

struct Size
{
    size_t Width;
    size_t Height;
};

class Window
{
  public:
    static Window Create(size_t width, size_t height);
    void Draw();
    bool ShouldClose();
    void SetShouldClose();
    std::vector<XEvent> GetEvents();
    Size GetSize() const;
    size_t GetWidth() const;
    size_t GetHeight() const;
    Display *GetDisplay() const;
    int GetScreen() const ;
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
