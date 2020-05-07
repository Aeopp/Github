#include "Timer.h"
#include <iostream>
#include "Util.h"
using namespace std::chrono;

bool Timer::Init()noexcept
{
	// 생성자와 Init 에서 Delta에 타임을 마킹해준다. 
	Delta = system_clock::now();
	return true; 
}

bool Timer::Render() const
{
	std::wcout << L"Sec : " << Elapsed << "  " << L"FPS : " << FPS << std::endl;
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

	Elapsed += BetWeen_f;

	// Global 델타와 경과시간을 계속 갱신해줌 
    // TODO :: 타이머 객체가 2개 이상일 경우 문제가 생김

	time::delta_sec = BetWeen_f;
	time::Elapsed_time = Elapsed;

	if (FrameTime += BetWeen_f;
		FrameTime > 1.f) {

		FPS = Fps_Count;
		Fps_Count = 0;

		FrameTime -= 1.f;
	}

	++Fps_Count;
	Delta = Current;

	return true; 
}
Timer::Timer() : 
	Elapsed{0}, 
	FrameTime{0},
	Name{0},
	Fps_Count{0},
	FPS{0},
	Delta{system_clock::now()}
{}

Timer::~Timer() noexcept
{
	Clear();
}
