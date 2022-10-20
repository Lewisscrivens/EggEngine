#pragma once

#include "Core/Window.h"
#include <Windows.h>

class WindowsWindow : public Window
{
    
public:

    WindowsWindow(const FWindowConfig& WindowConfig);
    ~WindowsWindow() override;

    /** Window creation/removal and initialisation. */
    static Window* CreateNativeWindow(const FWindowConfig& WindowConfig = FWindowConfig());
    
    /** Return the width and height. */
    int GetWidth() const override;
    int GetHeight() const override;

    /** Set/Getter for VSync capabilities. */
    void SetVSyncEnabled(bool bIsEnabled) override;

    /** Update window context. */
    int Update() const override;

    /** Handle Win32 API messages. */
    static LRESULT CALLBACK HandleWindowUpdate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT HandleWindowInstanceUpdate(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    
    HWND WindowHandle;
    WNDCLASS WindowsClass;
    HINSTANCE hInstance;
    std::string WindowName;
    bool bWindowClosed = false;
};
