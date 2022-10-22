
#include "EggPch.h"
#include "Engine.h"
#include "Platform/PlatformWindow.h"
#include "Logging/Log.h"

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
    // Initialise engine and modules.
    if (!Init())
    {
        EGG_LOG(Warning, "Engine failed to initialise! Exiting!");
        return -1;
    }

    // Enter application loop.
    while (bEngineRunning)
    {
        // Check if we have returned out of the app due to an error.
        const int UpdateStatus = AppWindow->Update();
        if (UpdateStatus < 1)
        {
            return UpdateStatus;
        }

        // Update engine frame time.
        EngineTiming.Update();
        Tick(EngineTiming.GetDeltaTime());

        
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

bool Engine::Init()
{
    // Init logging system.
    Log::Init();

    // Ensure an application exists.
    if (!AppInstance)
    {
        EGG_LOG(Warning, "Application could not be created! Exiting!");
        return false;
    }
    AppInstance->Init();
    
    // Initialise the window.
    if (!FPlatformWindow::InitNativeWindow())
    {
        return false;
    }
    AppWindow = UniquePtr<Window>(FPlatformWindow::CreateNativeWindow());
    
    bEngineRunning = true;
    return true;
}

void Engine::Tick(const float DeltaTime)
{
    if (AppInstance)
    {
        AppInstance->Tick(DeltaTime);
    }

    
}