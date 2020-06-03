#include "Mushroom.h"
#include "../CCore.h"
#include "../Resources/Texture.h"
#include "../Collision/ColinderRect.h"
#include "../Scene/CScene.h"

CMushroom::CMushroom() :
CMoveObj(),
m_fFireTime(0.f),
m_fFireLimitTime(1.13f) {}

CMushroom::CMushroom(const CMushroom& Obj) :
	CMoveObj(Obj){
	m_eDir = Obj.m_eDir;
	m_fFireTime = Obj.m_fFireTime;
	m_fFireLimitTime = Obj.m_fFireLimitTime;
};

bool CMushroom::Init()
{
	SetPos(1596.f, 1363.f);
	SetSize(100.f, 100.f);
	SetSpeed(300.f);
	SetPivot(0.5f, 0.5f);
	SetTexture(L"Orange", L"Orange_1.bmp");
	SetPhysics(true);

	m_pTexture->SetColorKey(RGB(255, 0, 255));

	m_eDir = MD_FRONT; 

	CColliderRect* pRC = AddCollider <CColliderRect>(L"Orange");

	pRC->SetRect(-50.f, -50.f, 50.f, 50.f);
	pRC->AddCollisionFunction(CS_ENTER, this, &CMushroom::CollisionBullet);

	SAFE_RELEASE(pRC);

	//CColliderRect* pRC = AddCollider<CColliderRect>(L"Orange");
	//pRC->SetRect(-50.f, -50.f, 50.f, 50.f);

	//pRC->AddCollisionFunction(CS_ENTER, this, &CMushroom::CollisionBullet);


	//SAFE_RELEASE(pRC);
	return true;
}


int CMushroom::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.x + m_tSize.x  >=
		GETRESOLUTION.iW) {
		m_tPos.x = GETRESOLUTION.iW - m_tSize.x;
		m_eDir = MD_BACK;
	}
	else if (m_tPos.x <= 0.f) {
		m_tPos.x = 0.f; 
		m_eDir = MD_FRONT;
	}
	m_fFireTime += fDeltaTime;
	if (m_fFireTime >= m_fFireLimitTime) {
		Fire(); 
		m_fFireTime -= m_fFireLimitTime;
	}
	return 0;
}

int CMushroom::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);

	return 0;
}

void CMushroom::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMushroom::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

	// TODO :: 디버그용 테스팅후 삭제
}

void CMushroom::Hit(CObj* const Target, float fDeltaTime)
{
	CObj::Hit(Target, fDeltaTime);
	if (Target->GetTag() == L"Player") {

	}
}

CMushroom* CMushroom::Clone()
{
	return new CMushroom{*this };
}

void CMushroom::CollisionBullet(CCollider* pSrc, CCollider* pDest, float fDeltaTime)
{
	MessageBox(NULL, L"충돌", L"충돌", MB_OK);
}

void CMushroom::Fire()
{
	CObj* pBullet = CObj::CreateCloneObj(L"Bullet",
		L"MushroomBullet", m_pScene->GetSceneType() , m_pLayer);

	dynamic_cast<CMoveObj*>(pBullet)->SetAngle(PI);

	float x = GetLeft() - (pBullet->GetSize().x * (1.f - pBullet->GetPivot().x));
	float y = GetCenter().y; 

	pBullet->SetPos(x, y);

	SAFE_RELEASE(pBullet);
}
