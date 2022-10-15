#pragma once

#include "EggCore.h"
#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std::chrono_literals;

/** Timer class to keep track of time in microseconds.
 *  NOTE: Could probably make some adjustments so FPS and DeltaTime are modular
 *       and not just stored from the seconds. */
class EGG_API Time
{
	
public:
	
	Time() = default;

	/** Update the the delta time and the rate per seconds this timer is running at. */
	void Update()
	{
		const auto TimeNow = Now();
		CurrentFrameTime = TimeNow.GetSeconds();
		DeltaTime = CurrentFrameTime - LastFrameTime;
		LastFrameTime = CurrentFrameTime;
		FramesPerSecond = 1.0f / DeltaTime;
		CurrentTimeMicroseconds = TimeNow.GetMicroseconds();
	}

	/** Creates a new time. */
	template<typename Rep, typename Period>
	constexpr Time(const std::chrono::duration<Rep, Period> &duration) :
		CurrentTimeMicroseconds(std::chrono::duration_cast<std::chrono::microseconds>(duration).count()) {}
	
	/** Gets CurrentTimeMicroseconds in seconds as Time. */
	template<typename T = float>
	constexpr static Time Seconds(const T &seconds)
	{
		return Time(std::chrono::duration<T>(seconds));
	}

	/** Gets CurrentTimeMicroseconds in milliseconds as Time. */
	template<typename T = int32_t>
	constexpr static Time Milliseconds(const T &milliseconds)
	{
		return Time(std::chrono::duration<T, std::micro>(milliseconds));
	}

	/** Gets CurrentTimeMicroseconds in microseconds as Time. */
	template<typename T = int64_t>
	constexpr static Time Microseconds(const T  &microseconds)
	{
		return Time(std::chrono::duration<T , std::micro>(microseconds));
	}

	/** Gets the time CurrentTimeMicroseconds in seconds of type T. */
	template<typename T = float>
	constexpr T GetSeconds() const
	{
		return static_cast<T>(CurrentTimeMicroseconds) / static_cast<T>(1000000);
	}

	/** Gets the time CurrentTimeMicroseconds in milliseconds of type T. */
	template<typename T = int32_t>
	constexpr auto GetMilliseconds() const
	{
		return static_cast<T>(CurrentTimeMicroseconds) / static_cast<T>(1000);
	}

	/** Gets the time CurrentTimeMicroseconds in microseconds of type T. */
	template<typename T = int64_t>
	constexpr auto GetMicroseconds() const
	{
		return static_cast<T>(CurrentTimeMicroseconds);
	}

	/** Returns the update rate that this timer is running at in seconds. */
	constexpr float GetDeltaTime() const
	{
		return DeltaTime;
	}

	/** Returns the frames per second this timer is running at. */
	constexpr float GetFramesPerSecond() const
	{
		return FramesPerSecond;
	}
	
	/** Gets the current time of this application. */
	static Time Now()
	{
		static const auto LocalEpoch = std::chrono::high_resolution_clock::now();
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - LocalEpoch);
	}

	/** Gets the current system time as a string. By default the format is %Y.%m.%d-%H.%M.%S
	 *  @param InFormat The format to put the time into. */
	static std::string GetTimeStamp(std::string_view InFormat = "%Y.%m.%d-%H.%M.%S")
	{
		auto TimeNow = std::chrono::system_clock::now();
		auto Time64 = std::chrono::system_clock::to_time_t(TimeNow);

		// Build time into string with format and return.
		std::stringstream OutStringStream;
		OutStringStream << std::put_time(std::localtime(&Time64), InFormat.data());
		return OutStringStream.str();
	}

	/** Operator overrides for comparing times. */

	template<typename Rep, typename Period>
	constexpr operator std::chrono::duration<Rep, Period>() const
	{
		return std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(CurrentTimeMicroseconds);
	}

	constexpr bool operator==(const Time &Other) const
	{
		return CurrentTimeMicroseconds == Other.CurrentTimeMicroseconds;
	}

	constexpr bool operator!=(const Time &Other) const
	{
		return CurrentTimeMicroseconds != Other.CurrentTimeMicroseconds;
	}

	constexpr bool operator<(const Time &Other) const
	{
		return CurrentTimeMicroseconds < Other.CurrentTimeMicroseconds;
	}

	constexpr bool operator<=(const Time &Other) const
	{
		return CurrentTimeMicroseconds <= Other.CurrentTimeMicroseconds;
	}

	constexpr bool operator>(const Time &Other) const
	{
		return CurrentTimeMicroseconds > Other.CurrentTimeMicroseconds;
	}

	constexpr bool operator>=(const Time &Other) const
	{
		return CurrentTimeMicroseconds >= Other.CurrentTimeMicroseconds;
	}

private:
	
	int64_t CurrentTimeMicroseconds = 0.0f;

	// Delta time calculation.
	float CurrentFrameTime = 0.0f;
	float LastFrameTime = 0.0f;
	float DeltaTime = 0.0f;
	float FramesPerSecond = 0.0f;
};