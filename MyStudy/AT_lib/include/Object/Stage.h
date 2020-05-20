#pragma once
#include "StaticObj.h"
class CStage :
	public CStaticObj
{
private:
	friend class CObj;
	friend class CScene;
public:
	CStage();
	 ~CStage()noexcept override ;
	CStage(const CStage& Obj);

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CStaticObj* Clone();
};

