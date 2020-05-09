#pragma once
#include "Core.h"
#include "Hero.h"
#include "Npc.h"

struct TProjectile
{
	FVector2D pos{ 0,0 };
	RECT   rtCollision;
	float fLifeTime;
	RECT   rtDesk;
	void  SetPos(FVector2D p)
	{
		SetPos(p[0], p[1]);
	}
	void  SetPos(float x, float y)
	{
		pos[0] = x;
		pos[1] = y;
		rtCollision.left = pos[0];
		rtCollision.top = pos[1];
		rtCollision.right =
			rtCollision.left + rtDesk.right;
		rtCollision.bottom =
			rtCollision.top + rtDesk.bottom;
	}
};
class Sample : public Engine
{
	int			LifeCounter;
	Hero	m_Hero;
	//TNpcObj		m_Npc;
	list<TNpcObj*>		m_NpcList;
	Actor		m_BackGround;
	Actor		m_Projectile;
	list<TProjectile>	m_ProjectileList;

	float	m_fNpcTime;
	float	HeroLifeTime;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
public:
	TNpcObj* AddNpc();
	bool RectInPt(RECT rt, POINT pt);
	bool RectInRect(RECT src, RECT desk);
	void SetLifeCounter();
public:
	Sample();
	~Sample();
};

