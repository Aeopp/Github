#pragma once
#include <Windows.h>
#include "helper.h"
class Actor
{
public:
	Actor(std::pair<float, float> set_pos);
public:
	std::pair<float, float> pos;
	const LONG Width = 50;
	const LONG Height = 50;
	const LONG DefaultLeft = 0;
	const LONG DefaultRight = DefaultLeft + Width;
	const LONG DefaultTop = 0;
	const LONG DefaultBottom = DefaultTop + Height;

	float speed = 100.f;
	RECT Rect{DefaultLeft,DefaultTop,DefaultRight,DefaultBottom };
	
	DECLARE_DEFAULT(Actor)
};

