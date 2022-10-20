#pragma once

#ifdef PLATFORM_WINDOWS

#include "Engine.h"
#include <Windows.h>

extern Application* CreateApplication();

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPreviewInstance, LPSTR lpCmdLine, int nCmdShow)
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
