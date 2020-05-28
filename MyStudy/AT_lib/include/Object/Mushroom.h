#pragma once
#include "MoveObj.h"

class CMushroom :
	public CMoveObj
{
private :
	friend class CObj;
	friend class CScene;
public:
	CMushroom(); 
	virtual ~CMushroom() noexcept {};
	CMushroom(const CMushroom& Obj);

	MOVE_DIR m_eDir; 
	float m_fFireTime;
	float m_fFireLimitTime;

	bool Init()override;
	int  Update(float fDeltaTime)override;
	int  LateUpdate(float fDeltaTime)override;
	void Collision(float fDeltaTime)override;
	void Render(HDC hDC, float fDeltaTime)override;
	void Hit(CObj* const Target, float fDeltaTime)override;
	CMushroom* Clone()override;
public :
	void CollisionBullet(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime);
private:
	void Fire(); 
};

