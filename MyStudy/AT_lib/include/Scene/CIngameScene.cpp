#include "CIngameScene.h"
#include "../Object/Player.h"
#include "../Object/Mushroom.h"
#include "../Object/Bullet.h"
#include "../Object/Stage.h"
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
	pBullet->SetSize(77.f, 77.f);
	pBullet->SetSpeed(660.f);
	SAFE_RELEASE(pBullet);
	
	CLayer* pStageLayer = FindLayer(L"Stage");

	CStage* pStage = CObj::CreateObj<CStage>(L"Stage", pStageLayer);
	SAFE_RELEASE(pStage); 


	return true;
}
