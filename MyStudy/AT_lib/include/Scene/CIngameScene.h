#pragma once
#include "CScene.h"


class CIngameScene :
	public CScene
{

public:
	friend class CSceneManager;
public : 
	~CIngameScene() noexcept;
	bool Init()override;
	
	void EndButtonCallback(float fTime);
};

