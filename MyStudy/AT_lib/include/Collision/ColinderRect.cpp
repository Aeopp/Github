#include "ColinderRect.h"
#include "../Object/Obj.h"
//#include "ColinderRect.h"
//#include "../Object/Obj.h"
//CColliderRect::CColliderRect()
//	:CCollider(){
//	m_eCollType = CT_RECT;
//}
//
//CColliderRect::CColliderRect(const CColliderRect& coll):
//	CCollider(coll){
//	m_tInfo = coll.m_tInfo;
//}
//
//CColliderRect::~CColliderRect()noexcept
//{
//}
//
//void CColliderRect::SetRect(float left, float top, float right, float bottom)
//{
//	m_tInfo.left = left;
//	m_tInfo.top = top;
//	m_tInfo.right = right;
//	m_tInfo.bottom = bottom;
//}
//
//bool CColliderRect::Init()
//{
//	return true;
//}
//
//void CColliderRect::Input(float fDeltaTime)
//{
//	CCollider::Input(fDeltaTime);
//}
//
//int CColliderRect::Update(float fDeltaTime){
//  CCollider::Update(fDeltaTime);
//  return 0;
//}
//
//int CColliderRect::LateUpdate(float fDeltaTime)
//{
//	CCollider::LateUpdate(fDeltaTime);
//	POSITION tPos = m_pObj->GetPos();
//	m_tWorldInfo.left = tPos.x + m_tInfo.left;
//	m_tWorldInfo.top = tPos.y + m_tInfo.top;
//	m_tWorldInfo.right = tPos.x + m_tInfo.right;
//	m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;
//	return  0;
//};
//bool CColliderRect::Collision(CCollider* pDest)
//{
//	CCollider::Collision(pDest);
//
//	switch (pDest->GetColliderType()) {
//	case CT_RECT:
//		return CollisionRectToRect(m_tWorldInfo, ((CColliderRect*)pDest)->GetWorldInfo());
//		break;
//	}
//	return false; 
//}
//
//void CColliderRect::Render(HDC hDC, float fDeltaTime)
//{
//	CCollider::Render(hDC, fDeltaTime);
//};
//
//CColliderRect* CColliderRect::Clone()
//{
//	return new CColliderRect(*this);
//};

CColliderRect::CColliderRect():
	CCollider()
{
	m_eCollType = CT_RECT;
}

CColliderRect::CColliderRect(const CColliderRect& coll):
CCollider(coll)
{
	m_tInfo = coll.m_tInfo;
}

void CColliderRect::SetRect(float l, float t, float r, float b)
{
	m_tInfo.left = l;
	m_tInfo.top = t;
	m_tInfo.right = r;
	m_tInfo.bottom = b;
}

CColliderRect::~CColliderRect()
{
}

bool CColliderRect::Init()
{
	return true;
}

void CColliderRect::Input(float fDeltaTime)
{
	CCollider::Input(fDeltaTime);
}

int CColliderRect::Update(float fDeltaTime)
{
	CCollider::Update(fDeltaTime);

	return 0;
}

int CColliderRect::LateUpdate(float fDeltaTime)
{
	CCollider::LateUpdate(fDeltaTime);

	POSITION tPos = m_pObj->GetPos();

	m_tWorldInfo.left = tPos.x + m_tInfo.left;
	m_tWorldInfo.top = tPos.y + m_tInfo.top;
	m_tWorldInfo.right = tPos.x + m_tInfo.right;
	m_tWorldInfo.bottom = tPos.y + m_tInfo.bottom;

	return 0;
};

bool CColliderRect::Collision(CCollider* pDest){
	switch (pDest->GetColliderType()) {
	case CT_RECT:
		return CollisionRectToRect(m_tWorldInfo,
			((CColliderRect*)pDest)->GetWorldInfo());
		break;
	}

	return false; 
}

void CColliderRect::Render(HDC hDC, float fDeltaTime)
{
	CCollider::Render(hDC, fDeltaTime);
}

CColliderRect* CColliderRect::Clone()
{
	return new CColliderRect(*this);
}
