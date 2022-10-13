#include "EngineApplication.h"
#include <iostream>

void EngineApplication::Init()
{
    Application::Init();

    std::cout << "Hello world";
}

void EngineApplication::Tick(const float DeltaTime)
{
    Application::Tick(DeltaTime);

    
}
