#pragma once
#include "Obj.h"
class CUI :
    public CObj
{
public: 
    CUI();   
    CUI(const   CUI& ui);
    virtual ~CUI() = 0;

	virtual bool Init() abstract;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Hit(CObj* const Target, float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CUI* Clone()abstract;
};

