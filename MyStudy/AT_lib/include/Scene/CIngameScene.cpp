#include "CIngameScene.h"

CIngameScene::~CIngameScene() noexcept
{
	
}

bool CIngameScene::Init()
{
	if (!CScene::Init())
		return false; 

	return true;
}
