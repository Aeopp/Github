#include "Mushroom.h"
#include "../CCore.h"
CMushroom::CMushroom(const CMushroom& Obj) :
	CMoveObj(Obj)
{
	m_eDir = Obj.m_eDir;
}

bool CMushroom::Init()
{
	SetPos(800.f, 100.f);
	SetSize(100.f, 100.f);
	SetSpeed(400.f);

	m_eDir = MD_FRONT; 

	return true;
}


int CMushroom::Update(float fDeltaTime)
{
	CMoveObj::Update(fDeltaTime);

	MoveYFromSpeed(fDeltaTime, m_eDir);

	if (m_tPos.y + m_tSize.y >=
		GETRESOLUTION.iH) {
		m_tPos.y = GETRESOLUTION.iH - m_tSize.y;
		m_eDir = MD_BACK;
	}
	else if (m_tPos.y <= 0.f) {
		m_tPos.y = 0.f; 
		m_eDir = MD_FRONT;
	}
	return 0;
}

int CMushroom::LateUpdate(float fDeltaTime)
{
	CMoveObj::LateUpdate(fDeltaTime);

	return 0;
}

void CMushroom::Collision(float fDeltaTime)
{
	CMoveObj::Collision(fDeltaTime);
}

void CMushroom::Render(HDC hDC, float fDeltaTime)
{
	CMoveObj::Render(hDC, fDeltaTime);

	Rectangle(hDC, m_tPos.x, m_tPos.y
		,m_tPos.x + m_tSize.x
		, m_tPos.y + m_tSize.y);
}
