#include "borderless.h"
#include <iostream>
#include <fstream>
#include <Psapi.h>
#include <windows.h>

int main()
{
    std::ifstream iniFile(INI_PATH);
    char executablePath[MAX_PATH];
    Window window;

    if (iniFile.good())
    {
        char windowTitle[Window::MaxTitleLength];

        int launchExe = GetPrivateProfileInt("Settings", INI_LAUNCH_EXE, 0, INI_PATH);
        GetPrivateProfileString("Settings", INI_EXE_PATH, "", executablePath, sizeof(executablePath), INI_PATH);
        GetPrivateProfileString("Settings", INI_WINDOW_TITLE, "", windowTitle, sizeof(windowTitle), INI_PATH);

        if (launchExe && strlen(executablePath) > 0)
        {
            std::cout << "Launching process: " << executablePath << std::endl;
            ShellExecute(NULL, "open", executablePath, NULL, NULL, SW_SHOWNORMAL);
        }

        if (strlen(windowTitle) > 0)
        {
            window.title = windowTitle;
        }
    }

    if (window.title.length() > 0)
    {
        std::cout << "Looking for " << window.title << std::endl;

        while (window.handle == nullptr)
        {
            window.handle = FindWindow(nullptr, window.title.c_str());
            Sleep(100);
        }

        std::cout << "Found " << window.title << "!" << std::endl;
    }
    else
    {
        window = SelectWindow();
    }

    Sleep(1000);
    SetBorderless(window.handle);
    SetForegroundWindow(window.handle);
    std::string newExecutablePath = GetProcessPathFromWindowHandle(window.handle);

    if (executablePath == newExecutablePath)
    {
        return 0;
    }

    WritePrivateProfileString("Settings", INI_LAUNCH_EXE, "1", INI_PATH);
    WritePrivateProfileString("Settings", INI_EXE_PATH, newExecutablePath.c_str(), INI_PATH);
    WritePrivateProfileString("Settings", INI_WINDOW_TITLE, window.title.c_str(), INI_PATH);

    return 0;
}

void GetWindows(std::vector<Window> &windowList)
{
    HWND hwnd = GetTopWindow(nullptr);

    while (hwnd)
    {
        char windowTitle[Window::MaxTitleLength];
        GetWindowText(hwnd, windowTitle, sizeof(windowTitle));

        if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0)
        {
            windowList.push_back(Window(windowTitle, hwnd));
        }

        hwnd = GetNextWindow(hwnd, GW_HWNDNEXT);
    }
}

void ListWindows(const std::vector<Window> &windowList)
{
    std::cout << "---------------------" << std::endl;
    std::cout << "|      Windows      |" << std::endl;
    std::cout << "---------------------" << std::endl;

    for (size_t i = 0; i < windowList.size(); i++)
    {
        std::cout << (i + 1) << ". " << windowList[i].title << std::endl;
    }
}

Window SelectWindow()
{
    std::vector<Window> windowList;
    GetWindows(windowList);
    ListWindows(windowList);
    int input = 0;

    std::cout << "Select: ";
    std::cin >> input;

    return windowList[input - 1];
}

std::string GetProcessPathFromWindowHandle(HWND wHandle)
{
    DWORD processId;
    GetWindowThreadProcessId(wHandle, &processId);

    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processId);
    if (hProcess == nullptr)
    {
        std::cerr << "Failed to open process" << std::endl;
        return "";
    }

    char szProcessPath[MAX_PATH];
    if (GetModuleFileNameEx(hProcess, nullptr, szProcessPath, MAX_PATH) == 0)
    {
        std::cerr << "Failed to get process path" << std::endl;
        return "";
    }

    CloseHandle(hProcess);

    return szProcessPath;
}

void SetBorderless(HWND wHandle)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    LONG style = GetWindowLongPtr(wHandle, GWL_STYLE);
    SetWindowLongPtr(wHandle, GWL_STYLE, style & ~WS_OVERLAPPEDWINDOW);

    SetWindowPos(wHandle, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
    MoveWindow(wHandle, 0, 0, screenWidth, screenHeight, false);
}