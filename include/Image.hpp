/*
#pragma once

#include "Window.hpp"
namespace xmaze
{

void CreateImage(const xmaze::Window& window)
{
    size_t image_bytes = width * height * 4;
    char *pixels = new char[image_bytes];
    std::memset(pixels, 0, image_bytes);

    window.m_BackBuffer =
        XCreateImage(window.m_Display, DefaultVisual(window.m_Display, window.m_Screen),
                     DefaultDepth(window.m_Display, window.m_Screen), ZPixmap, 0, pixels, width, height, 32, 0);
}

};
*/
