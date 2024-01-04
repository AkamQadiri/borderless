#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <string>

class Window
{
public:
    static const size_t MaxTitleLength = 256;

    std::string title;
    HWND handle = nullptr;

    Window() = default;
    Window(const char *title, HWND handle) : title(title), handle(handle) {}
};

#endif
