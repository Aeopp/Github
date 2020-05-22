#include "ColinderRect.h"
#include "../Object/Obj.h"
CColinderRect::CColinderRect()
	:CColinder(){
	m_eCollType = CT_RECT;
}

CColinderRect::CColinderRect(const CColinderRect& coll):
	CColinder(coll){
	m_tInfo = coll.m_tInfo;
}

CColinderRect::~CColinderRect()noexcept
{
}

void CColinderRect::SetRect(float left, float top, float right, float bottom)
{
	m_tInfo.left = left;
	m_tInfo.top = top;
	m_tInfo.right = right;
	m_tInfo.bottom = bottom;
}

bool CColinderRect::Init()
{
	return true;
}

void CColinderRect::Input(float fDeltaTime)
{
	CColinder::Input(fDeltaTime);
}

int CColinderRect::Update(float fDeltaTime){
return  CColinder::Update(fDeltaTime);
}

int CColinderRect::LateUpdate(float fDeltaTime)
{
	CColinder::LateUpdate(fDeltaTime);
	POSITION tPos = m_pObj->GetPos();
	m_tWorldInfo.left = tPos.x + m_tInfo.left;
	m_tWorldInfo.top = tPos.y + m_tInfo.top;
	m_tWorldInfo.right = tPos.x + m_tInfo.right;
	m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;
	return  0;
};
bool CColinderRect::Collision(CColinder* pDest)
{
	switch (pDest->GetColliderType()) {
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo, ((CColinderRect*)pDest)->GetWorldInfo());
		break;
	}
	return false; 
}

void CColinderRect::Render(HDC hDC, float fDeltaTime)
{
	CColinder::Render(hDC, fDeltaTime);
};

CColinderRect* CColinderRect::Clone()
{
	return new CColinderRect(*this);
};
