#include <X11/Xutil.h>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>

#include "Window.hpp"

namespace xmaze
{

xmaze::Window xmaze::Window::Create(size_t width, size_t height)
{
    xmaze::Window window;

    window.m_Display = XOpenDisplay(NULL);
    if (!window.m_Display)
    {
        std::cerr << "Unable to open window.m_Display" << std::endl;
        std::exit(1);
    }

    window.m_Screen = DefaultScreen(window.m_Display);

    window.m_Window = XCreateSimpleWindow(window.m_Display, RootWindow(window.m_Display, window.m_Screen), 0, 0, width,
                                          height, 0, BlackPixel(window.m_Display, window.m_Screen),
                                          WhitePixel(window.m_Display, window.m_Screen));

    XStoreName(window.m_Display, window.m_Window, "XMAZE");
    XSelectInput(window.m_Display, window.m_Window, ExposureMask | KeyPressMask);

    window.m_GC = XCreateGC(window.m_Display, window.m_Window, 0, NULL);
    if (!window.m_GC)
    {
        std::cerr << "Unable to create window.m_GC" << std::endl;
        std::exit(1);
    }

    size_t image_bytes = width * height * 4;
    char *pixels = new char[image_bytes];
    std::memset(pixels, 0, image_bytes);

    XSetForeground(window.m_Display, window.m_GC, BlackPixel(window.m_Display, window.m_Screen));

    XMapWindow(window.m_Display, window.m_Window);
    return window;
}

xmaze::Window::~Window()
{
    XFreeGC(m_Display, m_GC);
    XDestroyWindow(m_Display, m_Window);
    XCloseDisplay(m_Display);
}

std::vector<XEvent> xmaze::Window::GetEvents()
{
    XEvent event;
    std::vector<XEvent> events;
    size_t event_count = XPending(m_Display);
    events.reserve(event_count);
    for (size_t i = 0; i < event_count; ++i)
    {
        XNextEvent(m_Display, &event);
        events.push_back(event);
    }
    return events;
}

bool Window::ShouldClose()
{
    return m_ShouldClose;
}

void Window::SetShouldClose()
{
    m_ShouldClose = true;
}

Shape Window::GetShape() const
{
    XWindowAttributes attrs;
    XGetWindowAttributes(m_Display, m_Window, &attrs);
    size_t width = attrs.width;
    size_t height = attrs.height;
    return {width, height};
}

size_t Window::GetWidth() const
{
    return GetShape().Width;
}

size_t Window::GetHeight() const
{
    return GetShape().Height;
}

Display *Window::GetDisplay() const
{
    return m_Display;
}

int Window::GetScreen() const
{
    return m_Screen;
}

::Window Window::GetNativeWindow() const
{
    return m_Window;
}

GC Window::GetGC() const
{
    return m_GC;
}

}; // namespace xmaze
