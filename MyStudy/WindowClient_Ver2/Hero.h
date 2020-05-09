#pragma once
#include "Actor.h"
class Hero : public Actor
{
public:
	float	m_fSpeed;
public:
	bool	Frame();
public:
	Hero();
	virtual ~Hero();
};

