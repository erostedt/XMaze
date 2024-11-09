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

    window.m_BackBuffer =
        XCreateImage(window.m_Display, DefaultVisual(window.m_Display, window.m_Screen),
                     DefaultDepth(window.m_Display, window.m_Screen), ZPixmap, 0, pixels, width, height, 32, 0);

    XSetForeground(window.m_Display, window.m_GC, BlackPixel(window.m_Display, window.m_Screen));

    XMapWindow(window.m_Display, window.m_Window);
    window.m_Width = width;
    window.m_Height = height;
    return window;
}

void Window::Draw()
{
    XPutImage(m_Display, m_Window, m_GC, m_BackBuffer, 0, 0, 0, 0, m_Width, m_Height);
    XFlush(m_Display);
}

xmaze::Window::~Window()
{
    XDestroyImage(m_BackBuffer);
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

XImage *Window::Image()
{
    return m_BackBuffer;
}

bool Window::ShouldClose()
{
    return m_ShouldClose;
}

void Window::SetShouldClose()
{
    m_ShouldClose = true;
}

}; // namespace xmaze
