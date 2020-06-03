#pragma once
#include "MoveObj.h"

enum class EState :UINT8{
IDLE,
WALK,
JUMP,
HIT,
DIE,
};

class CMonster : public CMoveObj
{
private:
	friend class CObj;
	friend class CScene;
	void RandomState(float fDeltaTime)& ;
public :	 
	EState CurrentState = EState::IDLE;
	float StateRemaining = 2.f;
	CMonster();
	virtual ~CMonster()noexcept;
	CMonster(const CMonster& Monster);
	int m_iHP;
	bool m_bAttack;
	RECTANGLE Pow = { 0,0,0,0 };
	void Attack()&;
	bool bDead;
	void Dead()&;
	virtual bool Init(); 
	virtual CMonster* Clone();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	void ReleaseHitEvent(CObj* const Target, float fDeltaTime)override;
	void FirstHitEvent(CObj* const Target, float fDeltaTime)override;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;
};

