#pragma once
#include "Actor.h"
class Hero : public Actor
{
public:
	float	Speed;
public:
	bool	Frame();
public:
	Hero();
	virtual ~Hero();
};

