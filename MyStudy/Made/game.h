#pragma once

#include "Made.h"

class game
{
public : 
	void Run();
	bool bLoop = true;
	void Input_check()noexcept;
	RECT player_Rect{ 0,0,200,200 };
};

