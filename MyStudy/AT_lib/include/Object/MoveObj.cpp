#include "MoveObj.h"
#include <cmath>
CMoveObj::CMoveObj():
	CObj() ,
	m_fAngle{ 0.f} ,m_fSpeed { 100.f}{}

CMoveObj::CMoveObj(const CMoveObj& Obj):
	CObj(Obj) 
{
	m_fAngle = Obj.m_fAngle; 
	m_fSpeed = Obj.m_fSpeed; 
}

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.x += fDeltaTime * m_fSpeed
		* m_eDir;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.y += fDeltaTime * m_fSpeed* m_eDir;
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
void CMoveObj::MoveAngle( float fDeltaTime)
{
	m_tPos.x+=std::cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y+=std::sinf(m_fAngle) *  m_fSpeed * fDeltaTime;
};

void CMoveObj::MoveAngle()
{
	m_tPos.x += std::cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += std::sinf(m_fAngle) * m_fSpeed;
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
