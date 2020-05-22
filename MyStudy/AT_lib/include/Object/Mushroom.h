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

	virtual bool Init();
	virtual int  Update(float fDeltaTime);
	virtual int  LateUpdate(float fDeltaTime);
	virtual void Collision(float fDeltaTime);
	virtual void Render(HDC hDC, float fDeltaTime);
	virtual CMushroom* Clone()override;
public :
	void CollisionBullet(class CCollider* pSrc,
		class CCollider* pDest, float fDeltaTime); 
private:
	void Fire(); 
};

