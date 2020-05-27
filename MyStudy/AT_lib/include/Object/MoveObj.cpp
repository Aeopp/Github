#include "MoveObj.h"
#include <cmath>
CMoveObj::CMoveObj():
	CObj() ,
	m_fAngle{ 0.f} ,m_fSpeed { 100.f},
	m_bFalling{ true },
	m_bMove{ false },
	m_fForceOrigin{ 0.f },
	m_fForce{ 0.f } ,
	bJump{ false }{}

CMoveObj::CMoveObj(const CMoveObj& Obj) :
	CObj(Obj)
{
	m_fAngle = Obj.m_fAngle;
	m_fSpeed = Obj.m_fSpeed;

	/*m_bFalling = false;
	m_bMove = false;*/

	/*m_fForceOrigin = Obj.m_fForceOrigin;
	m_fForce = 0.f;*/
};

void CMoveObj::MoveXFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.x += fDeltaTime * m_fSpeed
		* m_eDir; m_bMove = true;
}

void CMoveObj::MoveYFromSpeed(float fDeltaTime, MOVE_DIR m_eDir)
{
	m_tPos.y += fDeltaTime * m_fSpeed* m_eDir; m_bMove = true;
}

void CMoveObj::Move(float x, float y, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime;
	m_tPos.y += y * fDeltaTime;

	m_bMove = true; 
}; 

void CMoveObj::Move(float x, float y)
{
	m_tPos.x += x;
	m_tPos.y += y;

	m_bMove = true;
};           

void CMoveObj::Move(const POSITION& tMove)
{
	m_tPos += tMove; m_bMove = true;
};

void CMoveObj::Move(const POSITION& tMove, float fDeltaTime)
{
	m_tPos += tMove * fDeltaTime; m_bMove = true;
}
void CMoveObj::MoveX(float x)
{
	m_tPos.x += x; m_bMove = true;
}
void CMoveObj::MoveX(float x, float fDeltaTime)
{
	m_tPos.x += x * fDeltaTime; m_bMove = true;
}
void CMoveObj::MoveY(float y)
{
	m_tPos.y += y ; m_bMove = true;
}
void CMoveObj::MoveY(float y, float fDeltaTime)
{
	m_tPos.y += y * fDeltaTime; m_bMove = true;
}
void CMoveObj::MoveAngle( float fDeltaTime)
{
	m_tPos.x+=std::cosf(m_fAngle) * m_fSpeed * fDeltaTime;
	m_tPos.y+=std::sinf(m_fAngle) *  m_fSpeed * fDeltaTime; m_bMove = true;
};

void CMoveObj::MoveAngle()
{
	m_tPos.x += std::cosf(m_fAngle) * m_fSpeed;
	m_tPos.y += std::sinf(m_fAngle) * m_fSpeed; m_bMove = true;
}
void CMoveObj::Jump()
{
	if (m_bFalling) {
		m_bFalling = true;
		m_fForce = m_fForceOrigin;

		
	}
}
void CMoveObj::JumpEnd()
{
		/*m_bFalling = false;
		m_fForce = 0.f;*/
};

void CMoveObj::Input(float fDeltaTime)
{
	CObj::Input(fDeltaTime);
}

int CMoveObj::Update(float fDeltaTime)
{
	if (m_bIsPhysics == true) {

		m_fGravityTime += fDeltaTime ;

		m_tPos.y += (GRAVITY * m_fGravityTime * m_fGravityTime);
	};

	CObj::Update(fDeltaTime);

	return 0; 
}

int CMoveObj::LateUpdate(float fDeltaTime)
{
	return CObj::LateUpdate(fDeltaTime);
}

void CMoveObj::Collision(float fDeltaTime)
{
	CObj::Collision(fDeltaTime);
};

void CMoveObj::Render(HDC hDC, float fDeltaTime)
{
	CObj::Render(hDC, fDeltaTime);

	//m_bMove = false;
};

