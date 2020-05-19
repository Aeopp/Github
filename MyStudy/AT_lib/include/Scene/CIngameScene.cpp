#include "CIngameScene.h"
#include "../Object/Player.h"
#include "../Object/Mushroom.h"
#include "../Object/Bullet.h"
#include "Layer.h"
CIngameScene::~CIngameScene() noexcept
{
	
}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	CLayer* pLayer = FindLayer(L"Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>(L"Player", pLayer); 
	SAFE_RELEASE(pPlayer);

	auto* pMushroom = CObj::CreateObj<CMushroom>
		(L"Mushroom", pLayer); 

	SAFE_RELEASE(pMushroom);

	CBullet* pBullet = CScene::CreateProtoType<CBullet>(L"Bullet");
	pBullet->SetSize(50.f, 50.f);

	SAFE_RELEASE(pBullet);

	

	return true;
}
