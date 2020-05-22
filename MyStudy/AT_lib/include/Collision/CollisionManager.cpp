#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "Colinder.h"

DEFINTION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager() {
};

CCollisionManager::~CCollisionManager() noexcept {
};

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
	list<CObj*>::iterator iter;
	list<CObj*>::iterator iterEnd = m_CollisionList.end();
	--iterEnd;
	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
		list<CObj*>::iterator iter1 = iter;
		++iter1;
		list<CObj*>::iterator iter1End = m_CollisionList.end();
		for (; iter1 != iter1End; ++iter) {
			Collision(*iter, *iter1, fDeltaTime);
		}
	}

	m_CollisionList.clear();
}

bool CCollisionManager::Collision(CObj* pSrc, CObj* pDest, float fDeltaTime)
{
	const list<CColinder*>* pSrcList = pSrc->GetColliderList();
	const list<CColinder*>* pDestList = pDest->GetColliderList();

	list<CColinder*>::const_iterator iterSrc;
	list<CColinder*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CColinder*>::const_iterator iterDest;
	list<CColinder*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false; 

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc) {
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest) {
			if ((*iterSrc)->Collision(*iterDest)) {
				bCollision = true; 

				// 첫 충돌이라는 의미
				if ((*iterSrc)->CheckCollisionList(*iterDest)) {
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					// 클라이언트가 첫 충돌시 처리해달라고 등록해놓은 함수 콜
					(*iterSrc)->CallFunction(CS_ENTER, *iterDest,
						fDeltaTime);
					(*iterSrc)->CallFunction(CS_ENTER, *iterSrc,
						fDeltaTime);
				}
				else { // 이미 오브젝트끼리 겹쳐있다	
					(*iterSrc)->CallFunction(CS_STAY, *iterDest,
						fDeltaTime);
					(*iterSrc)->CallFunction(CS_STAY, *iterSrc,
						fDeltaTime);
				}
			}
			// 충돌상태였었지만 해당 프레임 진입순간 두 오브젝트는 충돌상태에서 벗어났다.
			else if((*iterSrc)->CheckCollisionList(*iterDest)){
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc);

				(*iterSrc)->CallFunction(CS_LEAVE, *iterDest,
					fDeltaTime);
				(*iterSrc)->CallFunction(CS_LEAVE, *iterSrc,
					fDeltaTime);
			}
		}
	}
	return bCollision;
}
