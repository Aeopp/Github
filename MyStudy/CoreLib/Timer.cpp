#include "Timer.h"
#include "Util.h"
using namespace std::chrono;

bool Timer::Frame()
{
	const auto Current = system_clock::now();
	const auto BetWeen_Tick = duration_cast<milliseconds>(Current - Delta);
	const auto BetWeen_f = BetWeen_Tick.count() / 1000.;

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

