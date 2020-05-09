#pragma once
#include "Core.h"
#include "Hero.h"
#include "Npc.h"

struct TProjectile
{
	TPoint pos;
	RECT   rtCollision;
	float fLifeTime;
	RECT   rtDesk;
	void  SetPos(TPoint p)
	{
		SetPos(p.x, p.y);
	}
	void  SetPos(float x, float y)
	{
		pos.x = x;
		pos.y = y;
		rtCollision.left = pos.x;
		rtCollision.top = pos.y;
		rtCollision.right =
			rtCollision.left + rtDesk.right;
		rtCollision.bottom =
			rtCollision.top + rtDesk.bottom;
	}
};
class Sample : public TCore
{
	int			LifeCounter;
	THeroObj	m_Hero;
	//TNpcObj		m_Npc;
	list<TNpcObj*>		m_NpcList;
	TObject		m_BackGround;
	TObject		m_Projectile;
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

