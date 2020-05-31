#pragma once
#include "MoveObj.h"
class Weapon :  public CMoveObj
{
public:
	float Damage; 
	class CPlayer* Owner;
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
};

