#pragma once
#include "Made.h"
#include "Singleton.h"
#include "setup.h"
#include <vector>
#include "Actor.h"
#include <cmath>
#include "Time.h"
namespace Temp {
	class Bullet; 
	static std::vector<Temp::Bullet> Bullets;
	class Bullet {
	public:
		// 반지름이 먼저 초기화 되어야함
		static const inline float radius = 50.f;
		static const inline float speed = 100.f;
		RECT Sphere = { 0,0,static_cast<LONG>(radius),static_cast<LONG>(radius) };
		std::pair<LONG, LONG> Center{};
		float angle{ 0.f };
		bool Frame() & noexcept {
			Sphere.left += std::cos((angle)) * speed * Time::Instance().DeltaTime();
			Sphere.top += std::sin((angle)) * speed * Time::Instance().DeltaTime();

			Sphere.right += Sphere.left;
			Sphere.bottom += Sphere.top;
			
			// helper::clamp_pos(window::hWnd, Sphere, { radius,radius },Center);
			Ellipse(window::get_hdc().lock().get(), Sphere.left, Sphere.top, Sphere.right, Sphere.bottom);
			return true;
		}
	};
};

class game : public  SingleTon<game>
{
	friend class SingleTon<game>;
	friend struct std::unique_ptr<game>::deleter_type;
public :
	void Run();
	bool bLoop = true;
	void Input_check()noexcept;
	const LONG Width = 100;
	const LONG Height = 100;
	const LONG DefaultLeft = 0;
	const LONG DefaultRight = DefaultLeft + Width;
	const LONG DefaultTop = 0;
	const LONG DefaultBottom = DefaultTop + Height;
	
	float_t player_speed = setup::stat::PlayerSpeed;

	RECT player_Rect{ DefaultLeft,DefaultTop,DefaultRight,DefaultBottom };
	std::pair<LONG, LONG> Center; 
	 
	//static std::vector<Actor> Bullets;

	SINGLETON_DECLARE(game)
	DELETE_MOVE_COPY(game)
};

