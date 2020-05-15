#pragma once

#include "resource.h"
#include <algorithm>
#include <string>
#include "TypeAliaes.h"

namespace
{
	struct Area
	{
		bool bStart = false; 
		std::pair<int32, int32> Start = {};
		std::pair<int32, int32> End = {};
	};
}

static constexpr inline auto  MAX_LOADSTRING = 100ul;

namespace Window
{
	static inline Area MouseArea;
	static inline  HINSTANCE InstanceHandle;
	static inline double ResoluctionWidth = 1920.0 ;
	static inline double ResoluctionHeight = 1080.0 ;
	static inline double constexpr ResoluctionMin = 0.1;
	static inline double constexpr ResoluctionMax = 1.0;
	static inline const std::wstring Title = L"MapleStory";
	static inline const std::wstring WndClassName  = L"MapleStory";
	static constexpr void SetResoluctionScale(double Scale = 1.0)	{
		Scale  = std::clamp(Scale, ResoluctionMin, ResoluctionMax);
		ResoluctionHeight *=Scale;
		ResoluctionWidth *=  Scale; 
	}
}

