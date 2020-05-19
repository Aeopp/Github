#include "MoveObj.h"
#include <cmath>
CMoveObj::CMoveObj():
	m_fAngle{ 0.f} ,m_fSpeed { 100.f}   {}

CMoveObj::CMoveObj(const CMoveObj& Obj):
	CObj(Obj) 
{
	m_fAngle = Obj.m_fAngle; 
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.x += fDeltaTime * m_fSpeed
		* eDir;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir)
{
	m_tPos.y += fDeltaTime * m_fSpeed* eDir;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;
}; 

void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;
};           

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove;
};

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime;
}
void CMoveObj::MoveX(float x)
{
	m_tPos.x += x;
}
void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime; 
}
void CMoveObj::MoveY(float y)
{
	m_tPos.y += y ;
}
void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime; 
}
void CMoveObj::MoveAngle(float fSpeed, float fDeltaTime)
{
	m_tPos.x+=std::cosf(m_tPos.x) * fSpeed * fDeltaTime;
	m_tPos.y+=std::sinf(m_tPos.y)*  fSpeed * fDeltaTime;
};

void CMoveObj::MoveAngle(float fSpeed)
{
	m_tPos.x += std::cosf(m_tPos.x) * fSpeed;
	m_tPos.y += std::sinf(m_tPos.y) * fSpeed;
};

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	return 	CObj::Update(fDeltaTime);
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	return CObj::LateUpdate(fDeltaTime);
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
}

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC , fDeltaTime);
}
