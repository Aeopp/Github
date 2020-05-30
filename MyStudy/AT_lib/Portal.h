#pragma once
#include "include/Object/Obj.h"
#include <functional>

class Portal : public CObj
{
public :
	void Render(HDC hDC, float fDeltaTime)override; 
	bool Init()override;
	void Hit(CObj* const Target, float fDeltaTime)override; 
	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override; 
	std::function<void()> PortalEvent;
};

