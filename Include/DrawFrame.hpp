#pragma once

#include "Pixmap.hpp"
#include "Window.hpp"

namespace xmaze
{
class DrawFrame
{
  public:
    DrawFrame(xmaze::Window &window, xmaze::Pixmap &pixmap) : m_Window(window), m_Pixmap(pixmap)
    {
        auto display = m_Window.GetDisplay();
        auto gc = m_Window.GetGC();
        auto screen = m_Window.GetScreen();
        auto rect = m_Window.GetActiveArea();
        XSetForeground(display, gc, WhitePixel(display, screen));
        XFillRectangle(display, m_Pixmap.GetID(), gc, rect.Left(), rect.Top(), rect.Width(), rect.Height());
        XSetForeground(display, gc, BlackPixel(display, screen));
    }

    ~DrawFrame()
    {
        auto display = m_Window.GetDisplay();
        auto gc = m_Window.GetGC();
        auto rect = m_Window.GetActiveArea();

        XFlush(display);
        XCopyArea(display, m_Pixmap.GetID(), m_Window.GetNativeWindow(), gc, 0, 0, rect.Width(), rect.Height(), 0, 0);
    }

    const xmaze::Window &GetWindow() const
    {
        return m_Window;
    }

    xmaze::Pixmap &GetPixmap()
    {
        return m_Pixmap;
    }

  private:
    xmaze::Window &m_Window;
    xmaze::Pixmap &m_Pixmap;
};
}; // namespace xmaze
