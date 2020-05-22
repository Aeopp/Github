#include "Colinder.h"
#include "../Object/Obj.h"
CColinder::CColinder()
{
}

CColinder::~CColinder()noexcept
{
	// �ٸ� ������Ʈ�� �浹�� �ٸ� ������Ʈ�� �浹 ���̺��� �ڱ��ڽ��� ���������
	decltype(m_CollisionList)::iterator iterEnd = std::end(m_CollisionList);
	for (auto iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
		(*iter)->EraseCollisionList(this);
	}
}

CColinder::CColinder(const CColinder& coll) {
	*this = coll;
}
bool CColinder::Init()
{
	return true;
}

void CColinder::Input(float fDeltaTime)
{
}

int CColinder::Update(float fDeltaTime)
{
	return 0;
}

int CColinder::LateUpdate(float fDeltaTime)
{
	return 0;
}

bool CColinder::Collision(CColinder* pDest)
{
	return false;
}


void CColinder::Render(HDC hDC, float fDeltaTime)
{
}

CColinder* CColinder::Clone()
{
	return nullptr;
}
                        // ���� �ΰ� ������ !!!
bool CColinder::CollisionRectToRect(const RECTANGLE& src, const RECTANGLE& dest)
{
	//float src_x = (src.left + src.right) / 2;
	//float dest_x = (dest.left + dest.right) / 2;
	//float src_y = (src.top + src.bottom) / 2;
	//float dest_y = (dest.top  + dest.bottom) / 2;

	//float src_width = (src.right - src.left) / 2; 
	//float dest_width = (dest.right - dest .left) / 2;

	//float src_height = (src.bottom - src.top) / 2;
	//float dest_height = (dest.bottom - dest.top) / 2;

	//float x = std::abs(src_x - dest_x);
	//float y = std::abs(src_y - dest_y);

	//// x �� �¿� ���� �ι� ���� ������ ũ�ٸ� �浹���� ������
	//// y �� ���� ���� �ι� ���� ���ҹ� ũ�ٸ� �浹���� ������
	//if (x > src_width + dest_width) {
	//	return false; 
	//}
	//if (y > src_height + dest_height) {
	//	return false; 
	//}
	//return true; 

	if (src.left > dest.right)
		return false;
	else if (src.right < dest.left)
		return false;
	else if (src.top > dest.bottom)
		return false;
	else if (src.right < dest.left)
		return false;
	return true;
}

bool CColinder::CollisionRectToRect(const RECTANGLE& src,
	const RECTANGLE& dest)
{
	return false;
}
