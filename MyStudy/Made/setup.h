#pragma once
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
static constexpr inline auto  MAX_LOADSTRING = 100ul;

namespace setup {
	using MiliSec = std::chrono::duration<float, std::milli>;

	static inline double constexpr ResoluctionMin = 0.1;
	static inline double constexpr ResoluctionMax = 1.0;
	static inline const std::wstring Title = L"MapleStory";
	static inline const std::wstring WndClassName = L"MapleStory";

	static inline double ResoluctionWidth = 1920.0;
	static inline double ResoluctionHeight = 1080.0;

	constexpr float_t FPS = 60.f; 
	template<typename TimeTy=MiliSec> 
	constexpr TimeTy TimeUnit = TimeTy(1000.f);
	constexpr float_t Milisec = TimeUnit<MiliSec>.count();
	const MiliSec FramePerSecond = TimeUnit<MiliSec> / FPS;

	// FHD로 설정된 기본 해상도에서 스케일을 조정해주세요.
	static constexpr void SetResoluctionScale(double Scale = 1.0) {
		Scale = std::clamp(Scale, ResoluctionMin, ResoluctionMax);
		ResoluctionHeight *= Scale;
		ResoluctionWidth *= Scale;
	};
};