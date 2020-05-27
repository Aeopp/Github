#include "Bullet.h"
#include "../Resources/Texture.h"
#include "../Collision/ColinderRect.h"
CBullet::CBullet():
	m_fDist(0.f),
	m_fLimitDist{ 1000.f }{
}

CBullet::CBullet(const CBullet& Obj):
	CMoveObj(Obj)
{
	m_fLimitDist = Obj.m_fLimitDist;
	m_fDist = Obj.m_fDist;
}

bool CBullet::Init()
{
	SetSpeed(100.f);
	SetPivot(0.5f, 0.5f);
	SetTexture(L"Bullet", L"Skill_1.bmp");
	m_pTexture->SetColorKey(RGB(255, 0, 255));
	
	/*CColliderRect* pRC = AddCollider<CColliderRect>(L"Bullet");
	pRC->SetRect(-184.5f, -58.f, 184.5f, 58.f);
	SAFE_RELEASE(pRC);*/
	//CColliderRect* pRC = AddCollider<CColliderRect>(L"Bullet");
	// 369 116

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
}

void CBullet::Hit(CObj* const pDest, float fDeltaTime)
{
	CObj::Hit(pDest,fDeltaTime);
	
	if (GetTag() == L"PlayerBullet"
		&& pDest->GetTag() == L"Mushroom"   ){
		Die();
	}
	else if (GetTag() == L"MushroomBullet"
		&&pDest->GetTag() == L"Player") {
		Die();
	}
	//if (Target->GetTag() == this->GetTag()) {

	//}
	//else {
	//	Die();
	//}
}

CBullet* CBullet::Clone()
{
	return new CBullet{ *this }; 
}

