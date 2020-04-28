#include "Timer.h"
#include <iostream>
using namespace std::chrono;

bool Timer::Init()noexcept
{
	// 생성자나 Init 에서 Delta에 타임을 마킹해준다. 
	 // Delta = system_clock::now();
	return true; 
}

bool Timer::Render() const
{
	std::wcout << L"Sec : " << Tick << "  " << L"FPS : " << FPS << std::endl;
	return true;
}

bool Timer::Clear() noexcept
{

	

	return true; 
}

bool Timer::Frame()
{
	auto Current = system_clock::now();

	auto BetWeen_Tick = duration_cast<milliseconds>(Current - Delta);

	auto BetWeen_f = BetWeen_Tick.count() / 1000.;

	Tick += BetWeen_f;

	if (FrameTime += BetWeen_f;
		FrameTime > 1.) {

		FPS = Fps_Count;
		Fps_Count = 0;

		FrameTime -= 1.;
	}

	++Fps_Count;
	Delta = Current;

	return true; 
}
Timer::Timer() : 
	Tick{0}, 
	FrameTime{0},
	Name{0},
	Fps_Count{0},
	FPS{0},
	Delta{system_clock::now()}
{}
