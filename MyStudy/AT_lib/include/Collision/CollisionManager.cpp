#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "Colinder.h"

DEFINTION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager(){
}

CCollisionManager::~CCollisionManager() noexcept{
}

void CCollisionManager::AddObject(CObj* pObj)
{
	if (pObj->CheckCollider()) {
		m_CollisionList.push_back(pObj);
	}
	else {

	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2) {
		// TODO :: 체크 콜리전
		m_CollisionList.clear();
		return;
	};

}
