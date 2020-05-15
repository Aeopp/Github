#pragma once

#include "resource.h"
#include <algorithm>
#include <string>
#include <memory>
#include "TypeAliaes.h"
#include <Windows.h>
#include <sstream>
	

inline namespace
{
	struct Area
	{
		bool bStart = false;
		std::pair<int32, int32> Start = {};
		std::pair<int32, int32> End = {};
	};
};

class window
{
private:

public:
	static inline Area MouseArea = {};
	static inline HINSTANCE hInstance = nullptr;
	static inline HWND hWnd = nullptr;
	static inline std::shared_ptr<HDC__> hdc = nullptr;
	static inline auto _ReleaseDC = [](HDC hdc) {
		ReleaseDC(window::hWnd, hdc);
	};
public:
	static inline auto get_hdc() noexcept {
		return std::weak_ptr<HDC__>(hdc);
	};
	// First = X , Second = Y
	static inline auto GetMousePos(LPARAM lParam) {
		return std::pair{ lParam & 0x0000ffff, lParam >> 16 };
	}
	template<typename ...text>
	static inline auto format_text(text&&... texts) {
		std::wstringstream wss;
		(wss << ... << texts);
		return wss.str();
	};
};

static constexpr inline auto  MAX_LOADSTRING = 100ul;
class setup {
private:
	static inline double constexpr ResoluctionMin = 0.1;
	static inline double constexpr ResoluctionMax = 1.0;
	static inline const std::wstring Title = L"MapleStory";
	static inline const std::wstring WndClassName = L"MapleStory";
public:
	static inline double ResoluctionWidth = 1920.0;
	static inline double ResoluctionHeight = 1080.0;
	// FHD로 설정된 기본 해상도에서 스케일을 조정해주세요.
	static constexpr void SetResoluctionScale(double Scale = 1.0) {
		Scale = std::clamp(Scale, ResoluctionMin, ResoluctionMax);
		ResoluctionHeight *= Scale;
		ResoluctionWidth *= Scale;
	};
};



