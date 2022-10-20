#pragma once

/** Container for window initialisation properties. */
struct FWindowConfig
{
    std::string Name{};
    int Width = 0;
    int Height = 0;
    bool bMaximised = false;

    FWindowConfig(const std::string& WindowName = "Egg Window",
        int WindowWidth = 1280,
        int WindowHeight = 720,
        bool StartMaximised = false)
    {
        Name = WindowName;
        Width = WindowWidth;
        Height = WindowHeight;
        bMaximised = StartMaximised;
    }
};

/** Implementation of functions needed / used by the window and render API. */
class Window
{

public:

    Window() = default;
    virtual ~Window() = default;

    /** Window creation and initialisation. Returns pointer to the new window. */
    static Window* CreateNativeWindow(const FWindowConfig& WindowConfig = FWindowConfig());
    
    /** Update window context. */
    virtual int Update() const = 0;

    /** Return the width and height. */
    virtual int GetWidth() const  = 0;
    virtual int GetHeight() const  = 0;

    /** Set/Getter for VSync capabilities. */
    virtual void SetVSyncEnabled(bool bIsEnabled) = 0;
    bool IsVSyncEnabled() const
    {
        return bVSyncEnabled;
    }
    
protected:

    bool bVSyncEnabled = false;
    
};