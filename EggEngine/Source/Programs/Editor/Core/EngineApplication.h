#pragma once

#include "EggEngine.h"

/* Extended application class for this app from the EggEngine. */
class EngineApplication : public Application
{
public:

    /* Constructor and Destructor. */
    EngineApplication();

    /** Ran on application closed/exited. */
    void Shutdown() override;

protected:

    /* Ran at the start of the engine initialization. */
    void Init() override;

    /* Ran to tick each frame while in the loop. */
    void Tick(const float DeltaTime) override;
};

/* Define create app function to return this app to the engine entry point. */
inline Application* CreateApplication()
{
    return new EngineApplication();
}