#pragma once
#include "MoveObj.h"
class CBullet :
	public CMoveObj
{
private :
	friend class CObj;
	friend class CScene;
	public:
		CBullet();
		virtual ~CBullet() noexcept {};
		CBullet(const CBullet& Obj);
private:
	float m_fDist;
	float m_fLimitDist;
public:
	virtual bool Init();
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CBullet* Clone()override;
};

