#pragma once
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
static constexpr inline auto  MAX_LOADSTRING = 100ul;

// ���ӿ��� �ʿ��� ���� ���̺�
namespace setup {
	static inline double constexpr ResoluctionMin = 0.1;
	static inline double constexpr ResoluctionMax = 1.0;
	static inline const std::wstring Title = L"MapleStory";
	static inline const std::wstring WndClassName = L"MapleStory";

	static inline double ResoluctionWidth = 1600.0;
	static inline double ResoluctionHeight = 900.0;

	// FHD�� ������ �⺻ �ػ󵵿��� �������� �������ּ���.
	static constexpr void SetResoluctionScale(double Scale = 1.0) {
		Scale = std::clamp(Scale, ResoluctionMin, ResoluctionMax);
		ResoluctionHeight *= Scale;
		ResoluctionWidth *= Scale;
	};

	namespace time {}; 
	namespace stat {};
};

namespace setup::time {
	using MiliSec = std::chrono::duration<float, std::milli>;
	static constexpr float_t FPS = 60.f;
	template<typename TimeTy = MiliSec>
	static constexpr TimeTy TimeUnit = TimeTy(1000.f);
	static constexpr float_t Milisec = TimeUnit<MiliSec>.count();
	static const MiliSec FramePerSecond = TimeUnit<MiliSec> / FPS;
}

namespace setup::stat {
	static constexpr float_t PlayerSpeed = 300.f;
}