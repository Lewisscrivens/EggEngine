#pragma once

#include "Core/Window.h"
#include <Windows.h>

#define WIN32_CLASS_NAME L"w32_EggWindow"

class WindowsWindow : public Window
{
    
public:

    WindowsWindow(const FWindowConfig& WindowConfig);
    ~WindowsWindow() override;

    /** Init window class via win32 api. */
    static bool InitNativeWindow();
    
    /** Win32 window creation. Returns pointer to the new window as parent. */
    static Window* CreateNativeWindow(const FWindowConfig& WindowConfig = FWindowConfig());
    
    /** Return the width and height. */
    int GetWidth() const override;
    int GetHeight() const override;

    /** Set/Getter for VSync capabilities. */
    void SetVSyncEnabled(bool bIsEnabled) override;

    /** Update window context. */
    int Update() override;

    /** Handle Win32 API messages. */
    static LRESULT CALLBACK WindowProcessUpdates(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT WindowInstanceProcessUpdates(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    
    HWND WindowHandle;
    HINSTANCE hInstance;
    std::string WindowName;
    bool bWindowClosed = false;
};
