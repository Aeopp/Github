#pragma once
#include "ObjectSuper.h"
#include <chrono>
#include <string>
class Timer : public ObjectSuper 
{
public:
	virtual bool Init()noexcept override;
	virtual bool Render() const override;
	virtual bool Clear() noexcept override;
	virtual bool Frame()  override;


	Timer();
	virtual ~Timer()  noexcept;
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

