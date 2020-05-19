#pragma once
#include "Obj.h"

class CMoveObj :
	public CObj
{
private:
	float m_fAngle; 
	float m_fSpeed; 
protected: 
	CMoveObj();
	virtual ~CMoveObj() noexcept {}; 
	CMoveObj(const CMoveObj& Obj); 
public :
	void SetAngle(float fAngle) {
		m_fAngle = fAngle; 
	}
	void SetSpeed(float fSpeed) {
		m_fSpeed = fSpeed;
	}
	float GetAngle(float fSpeed)const {
		return m_fAngle; 
	}
	float  GetSpeed(float fSpeed)const {
		return m_fSpeed;
	}
	void MoveXFromSpeed(float fDeltaTime,
		MOVE_DIR eDir); 
	void MoveYFromSpeed(float fDeltaTime, MOVE_DIR eDir);
	void Move(float x, float y, float fDeltaTime); 
	void Move(float x, float y);
	void Move(const POSITION& tMove );
	void Move(const POSITION& tMove , float fDeltaTime);
	void MoveX(float x);
	void MoveX(float x,float fDeltaTime);
	void MoveY(float y);
	void MoveY(float y, float fDeltaTime);
	void MoveAngle(float fSpeed, float fDeltaTime); 
	void MoveAngle(float fSpeed);
public : 
	virtual bool Init() = 0; 
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
};

