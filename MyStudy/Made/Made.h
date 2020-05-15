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
	// 클라이언트는 소유권이 없음
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





