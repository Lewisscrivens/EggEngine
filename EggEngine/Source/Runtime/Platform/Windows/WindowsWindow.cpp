
#include "EggPch.h"
#include "WindowsWindow.h"
#include "Logging/Log.h"
#include "Utility/PathUtility.h"
#include "Utility/StringUtility.h"

bool WindowsWindow::InitNativeWindow()
{
    WNDCLASSEXW WindowsClass;

    ZeroMemory(&WindowsClass, sizeof(WindowsClass));
    WindowsClass.cbSize = sizeof(WindowsClass);
    WindowsClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WindowsClass.lpfnWndProc = WindowProcessUpdates;
    WindowsClass.hInstance = GetModuleHandleW(nullptr);
    WindowsClass.lpszClassName = WIN32_CLASS_NAME;
    WindowsClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    WindowsClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    
    // Load icon.
    const std::string IconDir = FPathUtil::GetEngineInstallDir() + "/EggEngine/Content/Icons/EggIcon.ico";
    WindowsClass.hIcon = static_cast<HICON>(LoadImageW(GetModuleHandleW(nullptr),
                                            FStringUtil::StringToWideString(IconDir).c_str(),
                                            IMAGE_ICON,
                                            0,
                                            0,
                                            LR_DEFAULTSIZE | LR_LOADFROMFILE));
    
    if (!RegisterClassExW(&WindowsClass))
    {
        EGG_LOG(Error, "Win32 API failed to register window class w32_EggWindow. See WindowsWindow InitNativeWindow!");
        return false;
    }

    return true;
}

Window* WindowsWindow::CreateNativeWindow(const FWindowConfig& WindowConfig)
{
    return new WindowsWindow(WindowConfig);
}

WindowsWindow::WindowsWindow(const FWindowConfig& WindowConfig)
{
    // Create/Show new window.
    auto WindowStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
    if (WindowConfig.bMaximised)
    {
        WindowStyle |= WS_MAXIMIZE;
    }

    WindowName = WindowConfig.Name;
    hInstance = GetModuleHandleW(nullptr);
    WindowHandle = CreateWindowExW(WS_EX_APPWINDOW,
                                   WIN32_CLASS_NAME,
                                   FStringUtil::StringToWideString(WindowName).c_str(),
                                   WindowStyle,
                                   CW_USEDEFAULT,
                                   CW_USEDEFAULT,
                                   WindowConfig.Width, 
                                   WindowConfig.Height,
                                   nullptr,
                                   nullptr,
                                   hInstance,
                                   nullptr);

    SetWindowLongPtrW(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    ShowWindow(WindowHandle, WindowConfig.bMaximised ? SW_MAXIMIZE : SW_SHOWDEFAULT);

    // TODO: Render custom border and buttons instead of using the default windows layout.
}

WindowsWindow::~WindowsWindow()
{
    UnregisterClassW(WIN32_CLASS_NAME, hInstance);
    DestroyWindow(WindowHandle);
}

int WindowsWindow::GetWidth() const
{
    return 0;
}

int WindowsWindow::GetHeight() const
{
    return 0;
}

void WindowsWindow::SetVSyncEnabled(bool bIsEnabled)
{
    
}

int WindowsWindow::Update()
{
    if (bWindowClosed)
    {
        EGG_LOG(Message, "Editor has been closed, shutting down...");
        return 0;
    }
    
    // Perform and dispatch message events from the window.
    MSG Msg;
    while (PeekMessageW(&Msg, WindowHandle, 0, 0, PM_REMOVE))
    {
        if (Msg.message == WM_QUIT)
        {
            bWindowClosed = true;
            continue;
        }

        TranslateMessage(&Msg);
        DispatchMessageW(&Msg);
    }

    return 1;
}

LRESULT CALLBACK WindowsWindow::WindowProcessUpdates(HWND InHandle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    const auto WindowInstancePtr = reinterpret_cast<WindowsWindow*>(GetWindowLongPtrW(InHandle, GWLP_USERDATA));
    if (WindowInstancePtr != nullptr)
    {
        return WindowInstancePtr->WindowInstanceProcessUpdates(InHandle, Msg, wParam, lParam);
    }
    
    return DefWindowProcW(InHandle, Msg, wParam, lParam);
}

LRESULT WindowsWindow::WindowInstanceProcessUpdates(HWND InHandle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    // Handle messages being sent from the window class.
    switch (Msg)
    {
    // On application closed.
    case WM_CLOSE:
    {
        bWindowClosed = true;
        return 0;
    }
    default: break;
    }
    
    return DefWindowProcW(InHandle, Msg, wParam, lParam);
}