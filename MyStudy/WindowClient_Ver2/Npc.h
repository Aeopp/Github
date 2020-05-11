#pragma once
#include "Actor.h"
class Npc : public Actor
{
public:
	FVector2D DirectionVector; 
	bool		m_bDead;
	float fDirectionX = 1.0f;
	float fDirectionY = 1.0f;
public:
	bool	Frame();
	bool Render(std::shared_ptr<HDC__>)override;
public:
	Npc();
	virtual ~Npc();
};

