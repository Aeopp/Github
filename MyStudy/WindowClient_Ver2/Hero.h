#pragma once
#include "Actor.h"
class Hero : public Actor
{
public:
	float	Speed;
public:
	bool	Frame();
	virtual bool		Render(std::shared_ptr<HDC__> hOffScreenDC)override;
public:
	Hero();
	virtual ~Hero();
};

