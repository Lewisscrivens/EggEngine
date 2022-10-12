#pragma once
#include <chrono>
#include "EggCore.h"

/** Timer class to keep track of time that the application has been opened. */
class EGG_API Time
{
public:

    /** Start the timer when created. */
    Time()
    {
        StartTimePoint = std::chrono::steady_clock::now();
    }

    /** Update the time per engine loop / tick frame. */
    void UpdateTime()
    {
        const auto CurrentTimePoint = std::chrono::steady_clock::now();
        const std::chrono::duration<float> CurrentFrameTime = CurrentTimePoint - LastFrameTimePoint;

        DeltaTime = CurrentFrameTime.count();
        CurrentTime = std::chrono::duration<float>(CurrentTimePoint - StartTimePoint).count();
        LastFrameTimePoint = CurrentTimePoint;
    }

    /** Returns current frame delta time. */
    float GetDeltaTime() const
    {
        return DeltaTime;
    }

    /** Returns current app time in seconds as a float. */
    float GetTimeSeconds() const
    {
        return CurrentTime;
    }

    /** Returns current app time in milliseconds as a float. */
    float GetTimeMilliseconds() const
    {
        return (CurrentTime / 1000.0f);
    }

private:

    /** Time since app initialized timer class. */
    std::chrono::steady_clock::time_point StartTimePoint;
    std::chrono::steady_clock::time_point LastFrameTimePoint;

    float DeltaTime = 0.0f;
    float CurrentTime = 0.0f;
};