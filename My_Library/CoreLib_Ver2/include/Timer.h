#pragma once
#include "Object.h"
#include <chrono>
class TTimer : public TBaseObject
{
public:
	tstring		Name;
	tstring		TimeOutputString;
	float_t		FramePerSecond;
	float_t		Timer;
	float_t		FrameTime;
	uint32_t FrameCount;
	int32_t			FPS;
public:
	using Clock = std::chrono::high_resolution_clock	;
	using  MilliSeconds= std::chrono::milliseconds			;
	Clock::time_point PrevTimePoint;
public:
	virtual bool	Init()	override;		
	virtual bool	Frame()	override;	         
	virtual bool	Render()	override;	
	virtual bool	Release()	override;	
public:
	TTimer();
	virtual ~TTimer()noexcept;


};


