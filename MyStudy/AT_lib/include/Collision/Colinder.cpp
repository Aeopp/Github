#include "Colinder.h"
#include <algorithm>
CCollider::CCollider()
{
}

CCollider::CCollider(const CCollider& coll)
{
	*this = coll; 
}

CCollider::~CCollider()
{
	/*std::for_each(std::begin(m_CollisionList),
		std::end(m_CollisionList),[this](CCollider* Target)
		{
			Target->EraseCollisionList(this); 
		});*/

	//list<CCollider*>::iterator iter;
	//list<CCollider*>::iterator iterEnd = m_CollisionList.end();

	//for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
	//	(*iter)->EraseCollisionList(this);
	//};
}

bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	if (src.left > dest.right)
		return false;
	else if (src.right < dest.left)
		return false;
	else if (src.top > dest.bottom)
		return false;
	else if (src.bottom < dest.top)
		return false;

	return true;
}

void CCollider::Input(float fDeltaTime)
{
}

int CCollider::Update(float fDeltaTime)
{
	return 0;
}

int CCollider::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CCollider::Collision(CCollider* pDest)
{
	return false; 
}

void CCollider::Render(HDC hDC, float fDeltaTime)
{
}












//#include "Colinder.h"
//#include "../Object/Obj.h"
//CCollider::CCollider()
//{
//}
//
//CCollider::~CCollider()noexcept
//{
//	// �ٸ� ������Ʈ�� �浹�� �ٸ� ������Ʈ�� �浹 ���̺��� �ڱ��ڽ��� ���������
//	list<CCollider*>::iterator iter;
//	list<CCollider*> ::iterator iterEnd = m_CollisionList.end();
//	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
//		(*iter)->EraseCollisionList(this); 
//	}
//	/*decltype(m_CollisionList)::iterator iterEnd = std::end(m_CollisionList);
//	for (auto iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
//		(*iter)->EraseCollisionList(this);
//	}*/
//}
//
//CCollider::CCollider(const CCollider& coll) {
//	*this = coll;
//}
//bool CCollider::Init()
//{
//	return true;
//}
//
//void CCollider::Input(float fDeltaTime)
//{
//}
//
//int CCollider::Update(float fDeltaTime)
//{
//	return 0;
//}
//
//int CCollider::LateUpdate(float fDeltaTime)
//{
//	return 0;
//}
//
//bool CCollider::Collision(CCollider* pDest)
//{
//	return false; 
//}
//
//
//void CCollider::Render(HDC hDC, float fDeltaTime)
//{
//}
//
//CCollider* CCollider::Clone()
//{
//	return nullptr;
//}
//                        // ���� �ΰ� ������ !!!
//bool CCollider::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
//{
//	//float src_x = (src.left + src.right) / 2;
//	//float dest_x = (dest.left + dest.right) / 2;
//	//float src_y = (src.top + src.bottom) / 2;
//	//float dest_y = (dest.top  + dest.bottom) / 2;
//
//	//float src_width = (src.right - src.left) / 2; 
//	//float dest_width = (dest.right - dest .left) / 2;
//
//	//float src_height = (src.bottom - src.top) / 2;
//	//float dest_height = (dest.bottom - dest.top) / 2;
//
//	//float x = std::abs(src_x - dest_x);
//	//float y = std::abs(src_y - dest_y);
//
//	//// x �� �¿� ���� �ι� ���� ������ ũ�ٸ� �浹���� ������
//	//// y �� ���� ���� �ι� ���� ���ҹ� ũ�ٸ� �浹���� ������
//	//if (x > src_width + dest_width) {
//	//	return false; 
//	//}
//	//if (y > src_height + dest_height) {
//	//	return false; 
//	//}
//	//return true; 
//
//	if (src.left > dest.right)
//		return false;
//	else if (src.right < dest.left)
//		return false;
//	else if (src.top > dest.bottom)
//		return false;
//	else if (src.bottom < dest.top)
//		return false;
//	return true;
//}
//


