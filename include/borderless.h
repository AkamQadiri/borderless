#ifndef BORDERLESS_H
#define BORDERLESS_H

#include <vector>
#include <string>

#include "Window.h"

#define INI_PATH ".\\borderless.ini"
#define INI_LAUNCH_EXE "LaunchExecutable"
#define INI_EXE_PATH "ExecutablePath"
#define INI_WINDOW_TITLE "WindowTitle"

void GetWindows(std::vector<Window> &windowList);
void ListWindows(const std::vector<Window> &windowList);
Window SelectWindow();
std::string GetProcessPathFromWindowHandle(HWND wHandle);
void SetBorderless(HWND wHandle);

#endif
