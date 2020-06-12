#pragma once
#include <utility>

struct RECTANGLE {
	float left{};  float  top{}; float right{};float  bottom{};
};

struct FVector2 {
	float x{};
	float y{};
};
struct FVector3 {
	float x{};
	float  y{};
	float z{};
};
struct FVector4 {
	float x{}; float  y{}; float  z{}; float  w{};
};

class Math
{
public :
	static inline constexpr double PI = 3.141592;
	static FVector3 ScreenToNDC(FVector2 Coordinate);
};

