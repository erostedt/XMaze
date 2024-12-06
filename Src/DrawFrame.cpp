#include "DrawFrame.hpp"
#include "Window.hpp"

namespace XMaze
{

DrawFrame::DrawFrame(Window &window) : m_Window(window)
{
    auto display = m_Window.GetDisplay();
    auto gc = m_Window.GetGC();
    auto screen = m_Window.GetScreen();
    auto rect = m_Window.GetActiveArea();
    XSetForeground(display, gc, WhitePixel(display, screen));
    XFillRectangle(display, m_Window.GetPixmap(), gc, rect.Left(), rect.Top(), rect.Width(), rect.Height());
    XSetForeground(display, gc, BlackPixel(display, screen));
}

DrawFrame::~DrawFrame()
{
    auto display = m_Window.GetDisplay();
    auto gc = m_Window.GetGC();
    auto rect = m_Window.GetActiveArea();
    auto pixmap = m_Window.GetPixmap();

    XFlush(display);
    XCopyArea(display, pixmap, m_Window.GetNativeWindow(), gc, 0, 0, rect.Width(), rect.Height(), 0, 0);
}

const Window &DrawFrame::GetWindow() const
{
    return m_Window;
}

}; // namespace XMaze
