#pragma once

#ifdef PLATFORM_WINDOWS

#include "Engine.h"

extern Application* CreateApplication();

/** Entry state for the engine. The engine will take car of the application initialisation. */
int main(int argc, char** argv)
{
	// Initialise/Start the Engine.
	const auto EngineInstance = new Engine();
	Application* AppInstance = CreateApplication();
	EngineInstance->SetApplication(AppInstance);
	EngineInstance->Start();
	delete EngineInstance;
	delete AppInstance;
}

#else

int main()
{
	// ONLY WINDOWS SUPPORTED FOR NOW.
}

#endif
