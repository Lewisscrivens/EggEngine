#pragma once

#include "Application.h"

/** Engine entry point. Manages and updates all modules / applications. */
class Engine
{

public:

    /** Instance startup and shutdown. */
    Engine();
    virtual ~Engine();
    
    /** Initialise the engine then start up the engine loop. */
    int Start();

    /** Returns the engine instance. */
    static Engine& GetEngine()
    {
        return *EngineInstance;
    }

    /** Set the active application for the engine. */
    void SetApplication(Application* InApplication)
    {
        AppInstance = InApplication;
    }

    /** Returns the application instance. */
    Application& GetApplication() const
    {
        return *AppInstance;
    }
    
protected:

    /** Initialise engine modules and application. */
    void Init();

    /** Shut down engine modules and application. */
    void Shutdown();

    /** Tick module threads and the application. */
    void Tick(const float DeltaTime);

private:

    /** Engine and app instance. */
    static Engine* EngineInstance;
    Application* AppInstance = nullptr;

    /** True while the engine is active and has not ran into any errors. */
    bool bEngineRunning = false;

    /** Engines lifetime instance. */
    EngineTime EngineTiming;
};