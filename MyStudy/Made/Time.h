#pragma once
#include <chrono>
#include "Singleton.h"
#include "Made.h"
#include <thread>
using namespace std::chrono_literals;
	// TODO :: private 기본 생성자 소멸자 선언하고 반드시 cpp에 구현
	// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) "helper.h"
class Time : public SingleTon<Time>
{
private: 
	friend class std::unique_ptr<Time>::deleter_type;
	friend class SingleTon<Time>;
public:
	using ms = std::chrono::duration<float, std::milli>;
	const ms FramePerSecond = 1000ms / 60.f;
	ms Delta;
	std::chrono::time_point<std::chrono::system_clock> prev_time= std::chrono::system_clock::now();
	std::chrono::time_point<std::chrono::system_clock> current_time =std::chrono::system_clock::now();

	inline auto DeltaTime()const&  noexcept {
		return (Delta.count()/ 1000.f);
	}
	bool Update() & noexcept;;

	SINGLETON_DECLARE(Time)
	DELETE_MOVE_COPY(Time)
};

