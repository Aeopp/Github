#pragma once
#include <thread>_dbdao.h
#include <utility>
#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <cmath>__msvc_all_public_headers.hpp
#include <numeric>

#define DECLARE_DEFAULT(Target)       \
public:\
Target()=default;\
virtual ~Target()noexcept = default;\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

#define SINGLETON_DECLARE(Target)        \
private:\
	Target(){};\
	virtual ~Target()noexcept{};       \

#define DEFAULT_MOVE_COPY(Target)       \
public:\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

// Singleton
// �̵� ī�� ���� 
#define DELETE_MOVE_COPY(Manager)   \
public:\
Manager(Manager&&)noexcept = delete;\
Manager& operator=(Manager&&)noexcept = delete;\
Manager(const Manager&) = delete;\
Manager& operator=(const Manager&) = delete;\

namespace math
{
	static inline float PI = 3.141592f; 
	static inline float Radian = 180.f / PI;
	static inline float DegreeToRadian(float Degree) noexcept {
		return Degree / math::Radian ; 
	}
	static inline float RadianToDegree(float Radian) noexcept {
		return Radian* math::Radian;
	};
}

namespace helper
{
	// ��ũ�� ��ǥ ����
	static inline  auto get_width_height(const RECT& Target) noexcept {
		return std::pair{ Target.right - Target.left,Target.bottom - Target.top };
	};
	// ���� Ŭ�� ��ǥ���� ȭ������� ������� ��ǥ ���� left , top ,right ,bottom 
	static inline  void clamp_pos(HWND hWnd,RECT& Target,const std::pair<LONG,LONG> width_height,std::pair<LONG,LONG>&Center) noexcept {
		RECT window_Rect;
		auto& [left, top, right, bottom] = Target;
		GetClientRect(hWnd, &window_Rect);

		auto& [window_left, window_top, window_right, window_bottom] = window_Rect;
		auto& [width,height] = width_height;
									// TODO :: ������� �����ѹ� ����
		left = std::clamp(left,     window_left, window_right - width);
		right = std::clamp(right,  window_left + width, window_right);
		top = std::clamp(top,       window_top,window_bottom-height);
		bottom = std::clamp(bottom,  window_top + height, window_bottom);

		Center.first = right - width / 2; 
		Center.second = bottom - height / 2;
	};
	template<typename StringType>
	constexpr StringType inline PathDelete(const StringType& FullPath)
	{
		StringType Filename = FullPath;

		auto erase_first = Filename.find_first_of('.');
		auto erase_last = Filename.find_last_of('/');

		if (erase_last != StringType::npos){
			Filename.erase(erase_first, erase_last + 1);
		}
		return Filename;
	}

	template<typename _Separator, typename ...Args>
	constexpr  void printer(_Separator&& Separator, Args&&... args) {
		(std::cout << ... << std::forward<Args>(args)) << std::forward<_Separator>(Separator);
	};
	template<typename Callable_Ty, typename ...Tys>
	constexpr  void Params(const Callable_Ty& Callable, Tys&&... Params)
	{
		(std::invoke(std::forward<decltype(Callable)>(Callable),
			std::forward<decltype(Params)>(Params)), ...);
	}
	template<typename Ty, typename ...Callable_Tys>
	constexpr  void Callables(const Ty& Param, Callable_Tys&& ... Callables)
	{
		(std::invoke(std::forward<decltype(Callables)>(Callables),
			std::forward<decltype(Param)>(Param)), ...);
	}

	template<typename Init, typename... Tys>
	constexpr auto Init_diff(Init&& Start, Tys&&... Params)
	{
		return (Start - ... - Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Sum(Init&& Start, Tys&&... Params)
	{
		return (Start + ... + Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Multiply(Init&& Start, Tys&&... Params)
	{
		return (Start * ... * Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Division(Init&& Start, Tys&&... Params)
	{
		return (Start * ... * Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Average(Init&& Start, Tys&&... Params)
	{
		return ((Start * ... * Params) / (sizeof...(Params) + 1));
	};
}