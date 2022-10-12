#pragma once

#ifdef PLATFORM_WINDOWS

#include "Application.h"

/** Needs creating in each sub application to this engine. */
extern Application* CreateApplication();

/** Entry state for the Windows Application. Create a window and enter while loop to receive and dispatch messages for created window class. */
int main(int argc, char** argv)
{
	// Initialise application.
	Application* ActiveApplication = CreateApplication();

	// Start the application loop.
	ActiveApplication->Start();
	delete ActiveApplication;
}

#else

int main()
{
	// ONLY WINDOWS SUPPORTED FOR NOW.
}

#endif
