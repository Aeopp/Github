#pragma once
#include "Object.h"
#include <chrono>
class Timer : public Object
{
public:
	tstring		Name;
	tstring		TimeOutputString;
	float_t		FramePerSecond;
	float_t		Time;
	float_t		FrameTime;
	uint32_t FrameCount;
	int32_t			FPS;
public:
	using Clock = std::chrono::high_resolution_clock	;
	using  MilliSeconds= std::chrono::milliseconds			;
	Clock::time_point PrevTimePoint;
public:	
	 bool	Frame()	override;	         
	 bool	Render()override;	
public:
	Timer();
	virtual ~Timer()noexcept;
	Timer(Timer&&)                  noexcept = default;
	Timer(const Timer&)             noexcept = default;
	Timer& operator=(Timer&&)        noexcept = default;
	Timer& operator=(const Timer&)  noexcept = default;
};


