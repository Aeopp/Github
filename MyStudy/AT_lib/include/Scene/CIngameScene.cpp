#include "CIngameScene.h"
#include "../Object/Player.h"
#include "../Object/Mushroom.h"
#include "Layer.h"
CIngameScene::~CIngameScene() noexcept
{
	
}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	CLayer* pLayer = FindLayer("Default");

	auto* pPlayer = CObj::CreateObj<CPlayer>("Player", pLayer);
	auto* pMushroom = CObj::CreateObj<CMushroom>
		("Mushroom", pLayer); 

   SAFE_RELEASE(pPlayer); 
   SAFE_RELEASE(pMushroom);

	return true;
}
