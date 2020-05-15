#include "game.h"
#include <algorithm>
#include "Time.h"
void game::Run()
{
	auto hdc = window::get_hdc().lock();
	Input_check();

	helper::clamp_pos(player_Rect,window::hWnd);
	auto& [left, top, right, bottom] = player_Rect;
	Rectangle(hdc.get(),left, top, right, bottom);
}

void game::Input_check() noexcept
{
	auto DeltaTime = Time::Instance().DeltaTime();

	auto& [left, top, right, bottom] = player_Rect;
	auto Vec = player_speed* DeltaTime; 

	if (GetAsyncKeyState('A') & 0x8000) {
		right -= (Vec);
		left -= (Vec);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
			right += (Vec);
		left += (Vec);
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		top -= (Vec);
		bottom -= (Vec);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		top += (Vec);
		bottom += (Vec);
	}
}



