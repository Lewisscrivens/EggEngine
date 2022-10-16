﻿
#include "EggPch.h"
#include "Engine.h"
#include "Log.h"

Engine* Engine::EngineInstance = nullptr;

Engine::Engine()
{
    EngineInstance = this;
}

Engine::~Engine()
{
    Shutdown();
}

int Engine::Start()
{
    // Run begin first and once.
    Init();

    // Enter application loop.
    while (bEngineRunning)
    {
        // Update engine frame time.
        EngineTiming.Update();
        Tick(EngineTiming.GetDeltaTime());

        if (EngineTiming.GetSeconds() > 5.0f)
        {
            bEngineRunning = false;
        }
    }

    return 0;
}

void Engine::Shutdown()
{
    if (AppInstance)
    {
        AppInstance->Shutdown();
    }

    
}

void Engine::Init()
{
    // Init logging system.
    Log::Init();

    // Ensure an application exists.
    if (!AppInstance)
    {
        EGG_LOG(Warning, "Application could not be created! Exiting!");
        return;
    }
    AppInstance->Init();
    
    bEngineRunning = true;
}

void Engine::Tick(const float DeltaTime)
{
    if (AppInstance)
    {
        AppInstance->Tick(DeltaTime);
    }

    
}