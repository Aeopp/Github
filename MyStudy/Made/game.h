#pragma once
#include "Made.h"
#include "Singleton.h"
#include "setup.h"
#include <vector>
#include "Actor.h"
class game : public  SingleTon<game>
{
	friend class SingleTon<game>;
	friend struct std::unique_ptr<game>::deleter_type;
public :
	void Run();
	bool bLoop = true;
	void Input_check()noexcept;

	LONG Width = 50;
	LONG Height = 50;
	const LONG DefaultLeft = 0;
	const LONG DefaultRight = DefaultLeft + Width;
	const LONG DefaultTop = 0;
	const LONG DefaultBottom = DefaultTop + Height;
	
	float_t player_speed = setup::stat::PlayerSpeed;

	RECT player_Rect{ DefaultLeft,DefaultTop,DefaultRight,DefaultBottom };

	SINGLETON_DECLARE(game)
	DELETE_MOVE_COPY(game)
};

