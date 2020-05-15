#pragma once

#include "Made.h"
#include "Singleton.h"
class game : public  SingleTon<game>
{
	friend class SingleTon<game>;
	friend struct std::unique_ptr<game>::deleter_type;
public :
	void Run();
	bool bLoop = true;
	void Input_check()noexcept;
	static constexpr LONG Width = 50;
	static constexpr LONG Height = 50;
	static constexpr LONG DefaultLeft = 0;
	static constexpr LONG DefaultRight = DefaultLeft + Width;
	static constexpr LONG DefaultTop = 0;
	static constexpr LONG DefaultBottom = DefaultTop + Height;
	
	static constexpr float_t player_speed = 300.f;

	RECT player_Rect{ DefaultLeft,DefaultTop,DefaultRight,DefaultBottom };

	SINGLETON_DECLARE(game)
	DELETE_MOVE_COPY(game)
};

