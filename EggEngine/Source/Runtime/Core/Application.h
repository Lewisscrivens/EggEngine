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
    
    /** Applications lifetime instance. */
    LifeTime AppLifeTime;
};

/** Define in the sub application. */
inline Application* CreateApplication();