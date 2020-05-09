#include "Timer.h"
#include <sstream>

bool	TTimer::Init()
{
	return true;
}
bool	TTimer::Frame()
{
	Clock::time_point Current= Clock::now();
	MilliSeconds ElapseClock = std::chrono::duration_cast<MilliSeconds>(Current - PrevTimePoint);
	
	FramePerSecond = ElapseClock.count() / 1000.0f;
	Timer += FramePerSecond;
	world::FramePerSecond = FramePerSecond;
	world::Timer = Timer;

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
	WStringStream << Timer << ':' << FPS;
	TimeOutputString = std::move(WStringStream.str());
	return true;
}
bool	TTimer::Render()
{
	return true;
}
bool	TTimer::Release()
{
	return true;
}

TTimer::TTimer() :
	FramePerSecond{ 0.0f },
Timer{ 0.0f },
FrameTime{ 0.0f },
FrameCount{ 0ul},
FPS{ 0l }
{
	PrevTimePoint = Clock::now();
}
TTimer::~TTimer() {
	
}
