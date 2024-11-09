#include "Window.hpp"
#include <X11/Xlib.h>

int main()
{
    size_t width = 800;
    size_t height = 600;
    xmaze::Window window = xmaze::Window::Create(width, height);

    while (!window.ShouldClose())
    {
        auto events = window.GetEvents();
        for (auto& event : events)
        {
            if (event.type == KeyPress &&
                XLookupKeysym(&event.xkey, 0) == 'q')
            {
                window.SetShouldClose();
            }
        }
    }
}
