#pragma once
#include "../Core/Ref.h"
class CColinder : 
	 public CRef
{
protected:
	friend class CObj;
public :
	CColinder();
	CColinder(const CColinder& coll);
	virtual ~CColinder()noexcept = 0;
protected:
	COLLIDER_TYPE m_eCollType;
	class CObj* m_pObj;
	POSITION m_tPrevPos; 
public:
	COLLIDER_TYPE GetColliderType()const {
		return m_eCollType;
	}
	class CObj* GetObj()const {
		return m_pObj;
	}
	void SetObj(class CObj* pObj) {
		m_pObj = pObj;
	}
public:
	virtual bool Init() = 0;
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CColinder* Clone() = 0;
};

