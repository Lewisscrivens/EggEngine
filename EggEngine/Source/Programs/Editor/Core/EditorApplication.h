#pragma once

#include "EggEngine.h"

/* Extended application class for this app from the EggEngine. */
class EditorApplication : public Application
{
public:

    /* Constructor and Destructor. */
    EditorApplication();
    
    /** Ran on application closed/exited. */
    void Shutdown() override;

protected:

    /* Ran at the start of the engine initialization. */
    void Init() override;

    /* Ran to tick each frame while in the loop. */
    void Tick(const float DeltaTime) override;
};

/** Return this editor application. */
inline Application* CreateApplication()
{
    return new EditorApplication();
}