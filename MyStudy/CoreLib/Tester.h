#pragma once
#include "Core.h"
#include "Hero.h"
#include "Npc.h"

class Tester : public Core
{
private:
	HDC _HScreenDC;
	HDC _HOffScreenDC;
	HBITMAP _HOffScreenBitmap;
	AHero _Hero;
	std::vector<ANpc> _Npcs;
	Mesh _BackGround;
protected: 
	virtual bool Frame()override; 
	virtual bool Render()override;
	virtual bool Init()noexcept override;
	virtual bool Clear()noexcept override;
};

