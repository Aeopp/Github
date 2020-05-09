#include "Timer.h"
#include <sstream>


bool	Timer::Frame()
{
	Clock::time_point Current= Clock::now();
	MilliSeconds ElapseClock = std::chrono::duration_cast<MilliSeconds>(Current - PrevTimePoint);
	
	FramePerSecond = ElapseClock.count() / 1000.0f;
	Time += FramePerSecond;
	World::FramePerSecond = FramePerSecond;
	World::Timer = Time;

	FrameTime += FramePerSecond;
	if (FrameTime > 1.0f)
	{
		FPS = FrameCount;
		FrameCount = 0;
		FrameTime = FrameTime - 1.0f;
	}
	FrameCount++;

	PrevTimePoint = Current;

	wstringstream  WStringStream;
	WStringStream << Time << ':' << FPS;
	TimeOutputString = std::move(WStringStream.str());
	return true;
}
bool	Timer::Render()
{
	return true;
}
Timer::Timer() :
	FramePerSecond{ 0.0f },
	Time{ 0.0f },
FrameTime{ 0.0f },
FrameCount{ 0ul},
FPS{ 0l }
{
	PrevTimePoint = Clock::now();
}
Timer::~Timer() {
	
}
