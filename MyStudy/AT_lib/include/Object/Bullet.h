#pragma once
#include "MoveObj.h"
class CBullet :
	public CMoveObj
{
	public:
		CBullet() {};
		virtual ~CBullet() noexcept {};
		CBullet(const CBullet& Obj);

		virtual bool Init();
		virtual int  Update(float fDeltaTime);
		virtual int  LateUpdate(float fDeltaTime);
		virtual void Collision(float fDeltaTime);
		virtual void Render(HDC hDC, float fDeltaTime);
};

