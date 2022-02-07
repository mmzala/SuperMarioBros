#include "Timer.h"

using namespace std::chrono;

Timer::Timer()
	:
	lastUpdate(steady_clock::now())
{}

float Timer::Mark()
{
	const auto old = lastUpdate;
	lastUpdate = steady_clock::now();
	const duration<float> frameTime = lastUpdate - old;

	return frameTime.count();
}

float Timer::Peek() const
{
	return duration<float>(steady_clock::now() - lastUpdate).count();
}
