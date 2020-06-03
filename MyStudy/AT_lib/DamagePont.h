#pragma once
#include "include/Object/StaticObj.h"
#include <vector>
class DamagePont : public CStaticObj
{
public :
	std::vector<class CTexture*> Ponts;
	bool bRender = false; 
	float RenderDelta = 0.3f;
	int CurrentPrintDamage{};
	POSITION DamagePosition{};
	virtual bool Init();
	virtual DamagePont* Clone();
	// std::vector<class CTexture*> Textures;
	void Render(HDC hDC, float fDeltaTime)override;
	void DamagePrint(POSITION PrintPos,int Damage);
	int  Update(float fDeltaTime)override; 
};

