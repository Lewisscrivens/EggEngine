#include "Application.h"

Application* Application::ActiveApplication = nullptr;

Application::Application()
{
	ActiveApplication = this;
}

int Application::Start()
{
	// Run begin first and once.
	Init();

	// Enter infinite loop.
	while (bAppRunning)
	{
        // Update engine frame time.
		ApplicationTime.UpdateTime();
        Tick(ApplicationTime.GetDeltaTime());


	}

    return 0;
}

void Application::Init()
{
	
}

void Application::Tick(const float DeltaTime)
{

}