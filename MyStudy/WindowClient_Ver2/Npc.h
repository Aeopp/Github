#pragma once
#include "Actor.h"
class TNpcObj : public Actor
{
public:
	bool		m_bDead;
	float fDirectionX = 1.0f;
	float fDirectionY = 1.0f;
public:
	bool	Frame();
public:
	TNpcObj();
	virtual ~TNpcObj();
};

