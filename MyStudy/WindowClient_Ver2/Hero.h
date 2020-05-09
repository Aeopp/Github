#pragma once
#include "Actor.h"
class THeroObj : public Actor
{
public:
	float	m_fSpeed;
public:
	bool	Frame();
public:
	THeroObj();
	virtual ~THeroObj();
};

