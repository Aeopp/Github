#include "Bullet.h"

CBullet::CBullet():
	m_fDist(0.f),
	m_fLimitDist{ 500.f }
{
}

CBullet::CBullet(const CBullet& Obj):
	CMoveObj(Obj)
{
	m_fLimitDist = Obj.m_fLimitDist;
	m_fDist = Obj.m_fDist;
}

bool CBullet::Init()
{
	SetSpeed(20000000000.f);
	 
	return true;
}

int CBullet::Update(float fDeltaTime)
{
	 CMoveObj::Update(fDeltaTime);
	 
	 MoveAngle(fDeltaTime);
	 m_fDist += GetSpeed() * fDeltaTime;

	 if (m_fDist >= m_fLimitDist)
		 Die(); 

	 return 0; 
}

int CBullet::LateUpdate(float fDeltaTime)
{
	return CMoveObj::LateUpdate(fDeltaTime);
}

void CBullet::Collision(float fDeltaTime)
{
	return CMoveObj::Collision( fDeltaTime);

}

void CBullet::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC,fDeltaTime); 

	Ellipse(hDC, m_tPos.x, m_tPos.
		y, m_tPos.x +
		m_tSize.x, m_tPos.y + m_tSize.y); 
}

CBullet* CBullet::Clone()
{
	return new CBullet{ *this }; 
}
