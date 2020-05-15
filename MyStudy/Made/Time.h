#pragma once
#include <chrono>
#include "Singleton.h"
#include "Made.h"
#include <thread>
#include "setup.h"
using namespace std::chrono_literals;
	// TODO :: private 기본 생성자 소멸자 선언하고 반드시 cpp에 구현
	// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) "helper.h"
class Time : public SingleTon<Time>
{
private:
	friend class std::unique_ptr<Time>::deleter_type;
	friend class SingleTon<Time>;
public:
	using MiliSec = setup::time::MiliSec;

	const MiliSec TimeUnit = setup::time::TimeUnit<MiliSec>;
	const float_t Milisec = setup::time::Milisec;
	const MiliSec FramePerSecond = setup::time::FramePerSecond;
	MiliSec Delta;
	std::chrono::time_point<std::chrono::system_clock> prev_time{ std::chrono::system_clock::now() };
	std::chrono::time_point<std::chrono::system_clock> current_time { std::chrono::system_clock::now()};
	
	// slowly.... faster.... 
	float_t timeScale{ 1.f }; 

	inline auto DeltaTime()const&  noexcept {
		return (Delta.count() / Milisec) * timeScale ;
	}

	bool Update() & noexcept;;

	SINGLETON_DECLARE(Time)
	DELETE_MOVE_COPY(Time)
};

