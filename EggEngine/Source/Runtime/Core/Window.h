#pragma once

/** Container for window initialisation properties. */
struct FWindowConfig
{
    std::string Name{};
    unsigned int Width;
    unsigned int Height;

    FWindowConfig(const std::string& WindowName = "Default Window",
        unsigned int WindowWidth = 1280,
        unsigned int WindowHeight = 720)
    {
        Name = WindowName;
        Width = WindowWidth;
        Height = WindowHeight;
    }
};

/** Implementation of functions needed / used by the window and render API. */
class Window
{

public:
    
    virtual ~Window() = default;

    /** Update window context. */
    virtual void OnUpdate() = 0;

    /** Return the width and height. */
    virtual unsigned int GetWidth() const  = 0;
    virtual unsigned int GetHeight() const  = 0;

    /** Set/Getter for VSync capabilities. */
    virtual void SetVSyncEnabled(bool bIsEnabled) = 0;
    virtual void IsVSyncEnabled() = 0;

    /** Window creation and initialisation. */
    static Window* Create(const FWindowConfig& WindowConfig = FWindowConfig());
};