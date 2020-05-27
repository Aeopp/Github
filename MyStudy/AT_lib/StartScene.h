#pragma once
#include "include/Scene/CScene.h"

class CStartScene :public CScene
{
private:
	friend class CSceneManager;
public:
	CStartScene();
	~CStartScene();

	bool Init()override;  
};

