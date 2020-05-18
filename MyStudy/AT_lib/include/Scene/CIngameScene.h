#pragma once
#include "CScene.h"
class CIngameScene :
	public CScene
{
public : 
	~CIngameScene() noexcept;
	bool Init()override;
};

