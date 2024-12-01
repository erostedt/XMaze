#pragma once
#include <X11/Xlib.h>

#include "Window.hpp"

namespace xmaze
{
class Pixmap
{
  public:
    Pixmap(const xmaze::Window &window)
    {
        m_Display = window.GetDisplay();
        int screen = window.GetScreen();
        const auto rect = window.GetActiveArea();
        m_PixmapID = XCreatePixmap(m_Display, window.GetNativeWindow(), rect.shape.width, rect.shape.height,
                                   DefaultDepth(m_Display, screen));
    }

    ::Pixmap GetID()
    {
        return m_PixmapID;
    }

    ~Pixmap()
    {
        XFreePixmap(m_Display, m_PixmapID);
    }

  private:
    ::Pixmap m_PixmapID;
    ::Display *m_Display;
};
}; // namespace xmaze
