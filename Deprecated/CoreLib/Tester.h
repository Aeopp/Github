#pragma once
#include "Core.h"
#include "Hero.h"
#include "Npc.h"

class Tester : public Core
{
private:
	HDC_ptr _HScreenDC;
	HDC_ptr _HOffScreenDC;
	HBITMAP_ptr _HOffScreenBitmap;
	AHero _Hero;
	std::vector<ANpc> _Npcs;
	Mesh _BackGround;
protected: 
	virtual bool Frame()override; 
	virtual bool Render()override;
	virtual bool Init() override;
	virtual bool Clear()noexcept override;
};

