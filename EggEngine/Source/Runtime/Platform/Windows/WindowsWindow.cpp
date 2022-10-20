
#include "EggPch.h"
#include "WindowsWindow.h"
#include "Logging/Log.h"
#include "Utility/PathUtility.h"

Window* WindowsWindow::CreateNativeWindow(const FWindowConfig& WindowConfig)
{
    return new WindowsWindow(WindowConfig);
}

WindowsWindow::WindowsWindow(const FWindowConfig& WindowConfig)
{
    // Create window class.
    hInstance = GetModuleHandleW(nullptr);
    WindowsClass = {};
    WindowsClass.hInstance = hInstance;
    WindowsClass.lpfnWndProc = HandleWindowUpdate;
    WindowsClass.cbClsExtra = 0;
    WindowsClass.cbWndExtra = 0;
    WindowsClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    WindowsClass.hbrBackground = (HBRUSH)GetStockObject (BLACK_BRUSH);
    WindowsClass.style = CS_HREDRAW | CS_VREDRAW;
    
    const std::wstring NameWideStr = std::wstring(WindowConfig.Name.begin(), WindowConfig.Name.end());
    const wchar_t* NameWide = NameWideStr.c_str();
    WindowsClass.lpszClassName = NameWide;

    // Load icon.
    std::string IconDir = FPathUtil::GetEngineInstallDir() + "/EggEngine/Content/Icons/EggIcon.ico";
    const std::wstring IconWideStr = std::wstring(IconDir.begin(), IconDir.end());
    const wchar_t* IconWide = IconWideStr.c_str();
    const auto WindowIcon = LoadImageW(hInstance, IconWide, IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
    WindowsClass.hIcon = (HICON)WindowIcon;
    
    RegisterClass(&WindowsClass);
    
    // Create/Show new window.
    auto WindowStyle = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME;
    if (WindowConfig.bMaximised)
    {
        WindowStyle |= WS_MAXIMIZE;
    }

    WindowName = WindowConfig.Name;
    WindowHandle = CreateWindowExW(WS_EX_APPWINDOW, NameWide, NameWide, WindowStyle, CW_USEDEFAULT, CW_USEDEFAULT, WindowConfig.Width, 
        WindowConfig.Height, nullptr, nullptr, hInstance, nullptr);
    SetWindowLongPtrW(WindowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
    ShowWindow(WindowHandle, WindowConfig.bMaximised ? SW_MAXIMIZE : SW_SHOWDEFAULT);

    // TODO: Render custom border and buttons instead of using the default windows layout.
}

WindowsWindow::~WindowsWindow()
{
    UnregisterClass(WindowsClass.lpszClassName, hInstance);
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

int WindowsWindow::Update() const
{
    if (bWindowClosed)
    {
        EGG_LOG(Message, "Editor has been closed, shutting down...");
        return -1;
    }
    
    // Perform and dispatch message events from the window.
    MSG Msg;
    while (PeekMessage(&Msg, WindowHandle, 0, 0, PM_REMOVE))
    {
        //switch ((int)Msg.wParam)
        //{
        //default: break;
        //}

        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
	
    // Return nothing.
    return 0;
}

LRESULT CALLBACK WindowsWindow::HandleWindowUpdate(HWND InHandle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    const auto WindowInstancePtr = reinterpret_cast<WindowsWindow*>(GetWindowLongPtr(InHandle, GWLP_USERDATA));
    if (WindowInstancePtr != nullptr)
    {
        return WindowInstancePtr->HandleWindowInstanceUpdate(InHandle, Msg, wParam, lParam);
    }
    
    return DefWindowProc(InHandle, Msg, wParam, lParam);
}

LRESULT WindowsWindow::HandleWindowInstanceUpdate(HWND InHandle, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    // Handle messages being sent from the window class.
    switch ((int)Msg)
    {
    // On application closed.
    case WM_CLOSE:
    {
        bWindowClosed = true;
        break;
    }
    default: break;
    }
    
    return DefWindowProc (InHandle, Msg, wParam, lParam);
}