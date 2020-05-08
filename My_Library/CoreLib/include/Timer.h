#pragma once
#include "ObjectSuper.h"
#include <chrono>
#include <iostream>
#include <string>

class Timer : public Object
{
public:
	std::wstring CurrentTime; 
	//_Implementation
	bool Frame();
	bool inline Init()noexcept;
	bool inline Render();

	Timer() :
		Elapsed{ 0 },
		FrameTime{ 0 },
		Name{ 0 },
		Fps_Count{ 0 },
		FPS{ 0 },
		Delta{ std::chrono::system_clock::now() }
	{
		Init();
	};
	
	virtual ~Timer() noexcept
	{
		Clear();
	}

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





bool inline Timer::Init()noexcept
{
	// 생성자와 Init 에서 Delta에 타임을 마킹해준다. 
	Delta = std::chrono::system_clock::now();
	return true;
}
bool inline Timer::Render()
{
	std::wcout << CurrentTime;
	
	return true;
}
