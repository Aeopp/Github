#include "game.h"

void game::Run()
{
	Input_check();

	auto hdc = window::get_hdc().lock();

	Rectangle(hdc.get(),player_Rect.left, player_Rect.top, 
	player_Rect.right, player_Rect.right);
}

void game::Input_check() noexcept
{
	if (GetAsyncKeyState('A') & 0x8000) {
		player_Rect.right += 1;
		player_Rect.left += 1;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		player_Rect.right -= 1;
		player_Rect.left -= 1;
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		DestroyWindow(window::hWnd);
	}
		if (GetAsyncKeyState('S') & 0x8000) {

		}
	
}
