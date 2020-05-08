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
	// ��� �����Ǿ��� �ð�
	float_t Elapsed;
	// ������ �����ø��� ����
	float_t FrameTime;

	// Delta�� ���� Ÿ�� ��ŷ �ϸ鼭 ��� ����
	std::chrono::system_clock::time_point Delta;
	uint64_t Fps_Count; 
	uint64_t FPS; 
};





bool inline Timer::Init()noexcept
{
	// �����ڿ� Init ���� Delta�� Ÿ���� ��ŷ���ش�. 
	Delta = std::chrono::system_clock::now();
	return true;
}
bool inline Timer::Render()
{
	std::wcout << CurrentTime;
	
	return true;
}
