#pragma once
#include "MoveObj.h"

class CPlayer :
	public CMoveObj
{
private : 
	friend class CObj;
	friend class CScene;
	CPlayer();
	virtual ~CPlayer()noexcept;
	CPlayer(const CPlayer& Player); 
private:
	int m_iHP;
	bool m_bAttack;
	
public:
	RECTANGLE Pow = { 0,0,0,0 };
	Vector JumpVector;
	void Attack()&;

	bool bDead;

	virtual bool Init();
	virtual void Input(float fDeltaTime);
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CPlayer* Clone()override;
	void Fire(); 
	void Dead()&;
	virtual void Hit(CObj* const Target, float fDeltaTime)override;
};

