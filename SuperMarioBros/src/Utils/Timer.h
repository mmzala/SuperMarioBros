#pragma once

#include <chrono>

class Timer
{
public:
	Timer();

	/// <summary>
	/// Returns the time between the last time you called Mark() and now
	/// </summary>
	/// <returns> The time between the last time you called Mark() and now </returns>
	float Mark();

	/// <summary>
	/// Returns the time between the last time you called Mark() without resetting lastUpdate time
	/// </summary>
	/// <returns> The time between the last time you called Mark() </returns>
	float Peek() const;

private:
	std::chrono::steady_clock::time_point lastUpdate;
};

