#pragma once

#include "Engine.h"

extern Application* CreateApplication();

int Main()
{
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
	const int Result = Main();
	switch(Result)
	{
	case -1:
	{
		MessageBoxW(nullptr, L"An error has occured check logs!", L"Error", MB_OK | MB_ICONEXCLAMATION);
	}
	break;
	default: break;
	}
	
	return 0;
}

#endif