#pragma once

#include "EggCore.h"
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

/** A point in time. */
class EGG_API TimePoint
{

public:

	/** Creates a time point from a given duration.. */
	template<typename Rep, typename Period>
	constexpr TimePoint(const std::chrono::duration<Rep, Period> &InDuration) :
		TimePointMicroseconds(std::chrono::duration_cast<std::chrono::microseconds>(InDuration).count()) {}

	/** Gets the time TimePointMicroseconds in seconds of type T. */
	template<typename T = float>
	constexpr T GetSeconds() const
	{
		return static_cast<T>(TimePointMicroseconds) / static_cast<T>(1000000);
	}

	/** Gets the time TimePointMicroseconds in milliseconds of type T. */
	template<typename T = int32_t>
	constexpr T GetMilliseconds() const
	{
		return static_cast<T>(TimePointMicroseconds) / static_cast<T>(1000);
	}

	/** Gets the time TimePointMicroseconds in microseconds of type T. */
	template<typename T = int64_t>
	constexpr T GetMicroseconds() const
	{
		return static_cast<T>(TimePointMicroseconds);
	}

	/** Gets this time point as a string in hrs, minutes and seconds. */
	std::string GetString() const
	{
		const float ElapsedSeconds = GetSeconds();
		char OutString[128];
		if (sprintf_s<128>(OutString, "%02.0f:%02.0f:%02.0f",
			floor(ElapsedSeconds / 3600.0f),
			floor(fmod(ElapsedSeconds,3600.0f) / 60.0f),
			floor(fmod(ElapsedSeconds,60.0f))))
		{
			return OutString;
		}
		
		return "";
	}

	constexpr bool operator==(const TimePoint &Other) const
	{
		return TimePointMicroseconds == Other.TimePointMicroseconds;
	}

	constexpr bool operator!=(const TimePoint &Other) const
	{
		return TimePointMicroseconds != Other.TimePointMicroseconds;
	}

	constexpr bool operator<(const TimePoint &Other) const
	{
		return TimePointMicroseconds < Other.TimePointMicroseconds;
	}

	constexpr bool operator<=(const TimePoint &Other) const
	{
		return TimePointMicroseconds <= Other.TimePointMicroseconds;
	}

	constexpr bool operator>(const TimePoint &Other) const
	{
		return TimePointMicroseconds > Other.TimePointMicroseconds;
	}

	constexpr bool operator>=(const TimePoint &Other) const
	{
		return TimePointMicroseconds >= Other.TimePointMicroseconds;
	}
	
private:
	
	int64_t TimePointMicroseconds = 0.0f;
	
};

/** Lifetime timer. Keeps track of how long it has existed. */
class EGG_API LifeTime
{

public:

	/** Initialise time of creation. */
	LifeTime()
	{
		StartClock = std::chrono::high_resolution_clock::now();
	}

	/** Gets the current time in seconds of type T. */
	template<typename T = float>
	constexpr T GetSeconds() const
	{
		return Now().GetSeconds<T>();
	}

	/** Gets the current time in milliseconds of type T. */
	template<typename T = int32_t>
	constexpr auto GetMilliseconds() const
	{
		return Now().GetMilliseconds<T>();
	}

	/** Gets the current time in microseconds of type T. */
	template<typename T = int64_t>
	constexpr auto GetMicroseconds() const
	{
		return Now().GetMicroseconds<T>();
	}

	/** Gets the current time that this time instance has existed. */
	TimePoint Now() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - StartClock);
	}

	/** Operator overrides for comparing times. */

	constexpr bool operator==(const LifeTime &Other) const
	{
		return Now() == Other.Now();
	}

	constexpr bool operator!=(const LifeTime &Other) const
	{
		return Now() != Other.Now();
	}

	constexpr bool operator<(const LifeTime &Other) const
	{
		return Now() < Other.Now();
	}

	constexpr bool operator<=(const LifeTime &Other) const
	{
		return Now() <= Other.Now();
	}

	constexpr bool operator>(const LifeTime &Other) const
	{
		return Now() > Other.Now();
	}

	constexpr bool operator>=(const LifeTime &Other) const
	{
		return Now() >= Other.Now();
	}

protected:

	std::chrono::time_point<std::chrono::steady_clock> StartClock;
	
};

/** Engine timer class for calculating delta time and fps.
 *  NOTE: Could probably make some adjustments so FPS and DeltaTime are modular
 *       and not just stored from the seconds. */
class EGG_API EngineTime : public LifeTime
{
	
public:

	/** Update the the delta time and the rate per seconds this timer is running at. */
	void Update()
	{
		const auto TimeNow = Now();
		CurrentFrameTime = TimeNow.GetSeconds();
		DeltaTime = CurrentFrameTime - LastFrameTime;
		LastFrameTime = CurrentFrameTime;
		FramesPerSecond = 1.0f / DeltaTime;
	}

	/** Returns the update rate that this timer is running at in seconds. */
	float GetDeltaTime() const
	{
		return DeltaTime;
	}

	/** Returns the frames per second this timer is running at. */
	float GetFramesPerSecond() const
	{
		return FramesPerSecond;
	}
	
	/** Gets system time as a string. By default the format is %Y.%m.%d-%H.%M.%S
      *  @param InFormat The format to put the time into. */
	static std::string GetSystemTimeStamp(std::string_view InFormat = "%Y.%m.%d-%H.%M.%S")
	{
		auto TimeNow = std::chrono::system_clock::now();
		auto Time64 = std::chrono::system_clock::to_time_t(TimeNow);

		// Build time into string with format and return.
		std::stringstream OutStringStream;
		OutStringStream << std::put_time(std::localtime(&Time64), InFormat.data());
		return OutStringStream.str();
	}

private:
	
	// Time calculations.
	float CurrentFrameTime = 0.0f;
	float LastFrameTime = 0.0f;
	float DeltaTime = 0.0f;
	float FramesPerSecond = 0.0f;
};