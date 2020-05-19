#pragma once
#include "Obj.h"
class CStaticObj :
	public CObj
{
protected:
	CStaticObj();
	virtual ~CStaticObj()noexcept =0 ;
	CStaticObj(const CStaticObj& obj);
public: 
	virtual bool Init() = 0; 
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime); 
	virtual CStaticObj* Clone() = 0;
};

