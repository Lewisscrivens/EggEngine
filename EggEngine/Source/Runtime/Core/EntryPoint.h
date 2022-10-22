#pragma once

#include "Engine.h"

extern Application* CreateApplication();

int Main()
{
	// Initialise/Start the Engine.
	const auto EngineInstance = new Engine();
	Application* AppInstance = CreateApplication();
	EngineInstance->SetApplication(AppInstance);
	const int ReturnCode = EngineInstance->Start();
	delete EngineInstance;
	delete AppInstance;
	return ReturnCode;
}

#ifdef PLATFORM_WINDOWS

#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreviewInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return Main();
}

#endif