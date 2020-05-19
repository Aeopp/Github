#include "CIngameScene.h"
#include "../Object/Player.h"
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
	SAFE_RELEASE(pPlayer); 

	return true;
}
