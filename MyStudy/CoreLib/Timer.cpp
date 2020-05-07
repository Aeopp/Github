#include "Timer.h"
#include "Util.h"
using namespace std::chrono;

bool Timer::Frame()
{
	const auto Current = system_clock::now();
	const auto BetWeen_Tick = duration_cast<milliseconds>(Current - Delta);
	const auto BetWeen_f = BetWeen_Tick.count() / 1000.;

	Elapsed += BetWeen_f;

	// Global ��Ÿ�� ����ð��� ��� �������� 
	// TODO :: Ÿ�̸� ��ü�� 2�� �̻��� ��� ������ ����

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

