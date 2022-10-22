#pragma once

#if PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

struct FPlatformWindow
{

    /** Window creation and initialisation. Returns pointer to the new window. */
    static bool InitNativeWindow()
    {
    #if PLATFORM_WINDOWS
        return WindowsWindow::InitNativeWindow();
    #endif
    }
    
    /** Window creation. Returns pointer to the new window. */
    static Window* CreateNativeWindow(const FWindowConfig& WindowConfig = FWindowConfig())
    {
    #if PLATFORM_WINDOWS
            return WindowsWindow::CreateNativeWindow(WindowConfig);
    #endif
    }

};