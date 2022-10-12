#pragma once
#include "EggEngine.h"

/* Extended application class for this app from the EggEngine. */
class EngineApplication : public Application
{
public:

    /* Constructor and Destructor. */
    EngineApplication() = default;
    ~EngineApplication() = default;

protected:

    /* Ran at the start of the engine initialization. */
    void Init() override;

    /* Ran to tick each frame while in the loop. */
    virtual void Tick(const float DeltaTime);
};

/* Define create app function to return this app to the engine entry point. */
Application* CreateApplication()
{
    return new EngineApplication();
}