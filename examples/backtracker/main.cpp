#include "Window.hpp"
#include <X11/Xlib.h>
#include <memory>

struct PixmapDeleter
{
    void operator()(Pixmap* pixmap)
    {
        XFreePixmap(display, *pixmap);
    }

    Display *display;
};

std::unique_ptr<Pixmap, PixmapDeleter> CreatePixmap(const xmaze::Window& window)
{
    Pixmap* pixmap = new Pixmap;
    Display* display = window.GetDisplay();
    int screen = window.GetScreen();
    const auto [width, height] = window.GetSize();
    *pixmap = XCreatePixmap(display, window.GetNativeWindow(), width, height, DefaultDepth(display, screen));
    std::unique_ptr<Pixmap, PixmapDeleter> wrapped(pixmap, PixmapDeleter{display});
    return wrapped;
}

int main()
{
    size_t width = 800;
    size_t height = 600;
    xmaze::Window window = xmaze::Window::Create(width, height);
    auto pixmap = CreatePixmap(window);

    auto display = window.GetDisplay();
    auto gc = window.GetGC();
    auto screen = window.GetScreen();
    XSetForeground(display, gc, WhitePixel(display, screen));
    XFillRectangle(display, *pixmap, gc, 0, 0, 800, 600);
    XSetForeground(display, gc, BlackPixel(display, screen));
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
            if (event.type == KeyPress &&
                XLookupKeysym(&event.xkey, 0) == 'k')
            {
                XDrawLine(window.GetDisplay(), *pixmap, window.GetGC(), 0, 400, 799, 0);
                XFlush(window.GetDisplay());
                XCopyArea(display, *pixmap, window.GetNativeWindow(), gc, 0, 0, width, height, 0, 0);
            }
        }
    }
}
