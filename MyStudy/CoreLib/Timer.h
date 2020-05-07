#pragma once
#include "ObjectSuper.h"
#include <chrono>
#include <iostream>
#include <string>
class Timer : public ObjectSuper
{
public:
	//_Implementation
	bool Frame();
	bool inline Init()noexcept;
	bool inline Render();


	Timer();
	virtual ~Timer() noexcept;

	Timer(Timer&&) noexcept = default;
	Timer(const Timer&) = default;
	Timer& operator=(Timer&&) noexcept = default;
	Timer& operator=(const Timer&) = default;
 private : 
	std::wstring Name;
	// 계속 누적되어진 시간
	float_t Elapsed;
	// 프레임 루프시마다 갱신
	float_t FrameTime;

	// Delta에 이전 타임 마킹 하면서 계속 갱신
	std::chrono::system_clock::time_point Delta;
	uint64_t Fps_Count; 
	uint64_t FPS; 
};

Timer::Timer() :
	Elapsed{ 0 },
	FrameTime{ 0 },
	Name{ 0 },
	Fps_Count{ 0 },
	FPS{ 0 },
	Delta{std::chrono::system_clock::now() }
{
	Init();
}

Timer::~Timer() noexcept
{
	//TODO :: 추후에 가상함수로 바꾼다면 Clear 호출해선 안됨
	// 소멸 or 생성 스코프에서 가상함수는 작동하지 않는다.
	Clear();
}

bool inline Timer::Init()noexcept
{
	// 생성자와 Init 에서 Delta에 타임을 마킹해준다. 
	Delta = std::chrono::system_clock::now();
	return true;
}
bool inline Timer::Render()
{
	std::wcout << L"Sec : " << Elapsed << "  " << L"FPS : " << FPS << std::endl;
	return true;
}
