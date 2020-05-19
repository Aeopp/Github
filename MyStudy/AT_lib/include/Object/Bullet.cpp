#include "Bullet.h"

CBullet::CBullet():
	m_fDist(0.f),
	m_fLimitDist{ 500.f }
{
}

CBullet::CBullet(const CBullet& Obj)
{
	m_fLimitDist = Obj.m_fLimitDist;
	m_fDist = Obj.m_fDist;
}

bool CBullet::Init()
{
	return false;
}

int CBullet::Update(float fDeltaTime)
{
	 CMoveObj::Update(fDeltaTime);

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
}

CBullet* CBullet::Clone()
{
	return new CBullet{ *this }; 
}
