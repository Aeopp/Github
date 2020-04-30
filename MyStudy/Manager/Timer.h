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
	// ��� �����Ǿ��� �ð�
	float_t Elapsed;
	// ������ �����ø��� ����
	float_t FrameTime;

	// Delta�� ���� Ÿ�� ��ŷ �ϸ鼭 ��� ����
	std::chrono::system_clock::time_point Delta;
	uint64_t Fps_Count; 
	uint64_t FPS; 
};

