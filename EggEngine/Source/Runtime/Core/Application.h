#pragma once

#include "Time.h"
#include "EggCore.h"

/** Application interface. */
class EGG_API Application
{
	
public:

	/** Default app constructor and destructor. */
	Application() = default;
	virtual ~Application() = default;

	/** Ran when the engine is shutting the application down. */
	virtual void Shutdown() {}

    /** Ran to initialise application components. */
    virtual void Init() {}

    /** Ran to tick each frame while in the loop. */
    virtual void Tick(const float DeltaTime) {}

	/** Gets the applications lifetime. (The time the application has been active) */
	LifeTime GetApplicationLifeTime() const
	{
		return AppLifeTime;
	}

	/** Gets the application's name. */
	std::string GetName() const
	{
		return Name;
	}

	/** Gets the applications version. */
	std::string GetVersion() const
	{
		return Version;
	}

protected:

	/** Lifetime instance. */
	LifeTime AppLifeTime;

	/** Config settings. */
	std::string Name;
	std::string Version;
	
};

/** Define in the sub application. */
inline Application* CreateApplication();