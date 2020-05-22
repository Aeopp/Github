#pragma once
#include "Colinder.h"
class CColinderRect :
	public CColinder
{
protected:
	friend class CObj;
public:
	CColinderRect();
	CColinderRect(const CColinderRect& coll);
	virtual ~CColinderRect()noexcept;
private:
	RECTANGLE m_tInfo;
	RECTANGLE m_tWorldInfo;
public:
	RECTANGLE GetInfo()const {
		return m_tInfo;  
	}
	RECTANGLE GetWorldInfo()const {
		return m_tWorldInfo; 
	};	
	void SetRect(float left, float top, float right, float bottom);

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual bool Collision(CColinder* pDest);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColinderRect* Clone();
};

