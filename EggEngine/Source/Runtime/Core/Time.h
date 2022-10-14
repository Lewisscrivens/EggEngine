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

    /** Returns time stamp as string now. E.g 2022.10.14-01.31.54 */
    static String GetTimeStamp()
    {
        auto time = std::time(nullptr);
        auto time_info = std::localtime(&time);
        char buffer[128];
        int string_size = strftime(
            buffer, sizeof(buffer),
            "%Y.%m.%d-%H.%M.%S",
            time_info
        );

        return buffer;
    }

private:

    /** Time since app initialized timer class. */
    std::chrono::steady_clock::time_point StartTimePoint;
    std::chrono::steady_clock::time_point LastFrameTimePoint;

    float DeltaTime = 0.0f;
    float CurrentTime = 0.0f;
};