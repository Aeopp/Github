#include "Colinder.h"
#include "../Object/Obj.h"
CColinder::CColinder()
{
}

CColinder::~CColinder()noexcept
{
	// 다른 오브젝트와 충돌시 다른 오브젝트의 충돌 테이블에서 자기자신을 지워줘야함
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
                        // 로직 두개 동일함 !!!
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

	//// x 가 좌우 폭을 두번 더한 값보다 크다면 충돌하지 않은것
	//// y 가 상하 폭을 두번 더한 값소받 크다면 충돌하지 않은것
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
