#pragma once
#include "Time.h"
#include "EggCore.h"

class EGG_API Application
{
public:

	/** Default app constructor and destructor. */
	Application();
	virtual ~Application() = default;

	/** Starting function with while Loop which loops until application is exited through error or user. */
	virtual int Start();

	/** Static getters for the application for access by subclasses. */
	static Application& GetApplication()
	{
		return *ActiveApplication;
	}

	/** Is this application running. */
	bool IsAppRunning() const
	{
		return bAppRunning;
	}

protected:

    /** Ran on engine start for initialization of certain engine components. */
    virtual void Init();

    /** Ran to tick each frame while in the loop. */
    virtual void Tick(const float DeltaTime);

private:

	/** Static pointer to this app. */
	static Application* ActiveApplication;

    /** Timer for calculating engine time and delta time. */
    Time ApplicationTime;
	
	/** Is the app currently running? */
	bool bAppRunning = true;
};

/** Define in the sub application. */
inline Application* CreateApplication();