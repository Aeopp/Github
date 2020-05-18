#pragma once
#include <Windows.h>
#include "helper.h"
class Actor
{
public:
	Actor(std::pair<float,float> set_pos);
public:
	std::pair<float,float> Pos;
	LONG Width = 50;
	LONG Height = 50;

	float Speed = 100.f;
	RECT Rect{ 0,0,0,0 };

	DECLARE_DEFAULT(Actor)
};

