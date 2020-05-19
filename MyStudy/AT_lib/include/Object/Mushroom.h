#pragma once
#include "MoveObj.h"

class CMushroom :
	public CMoveObj
{
public:
	CMushroom() {}; 
	virtual ~CMushroom() noexcept {};
	CMushroom(const CMushroom& Obj);

	MOVE_DIR m_eDir; 

	virtual bool Init();
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

