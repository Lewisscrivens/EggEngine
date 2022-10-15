
#include "EggPch.h"
#include "Application.h"
#include "Log.h"

Application* Application::ActiveApplication = nullptr;

Application::Application()
{
	ActiveApplication = this;
}

int Application::Start()
{
	// Run begin first and once.
	Init();

	// Enter application loop.
	while (bAppRunning)
	{
        // Update engine frame time.
		ApplicationTime.Update();
        Tick(ApplicationTime.GetDeltaTime());

		
	}

    return 0;
}

void Application::Init()
{
	// Init logging system for the engine.
	Log::Init();
	
}

void Application::Tick(const float DeltaTime)
{

}