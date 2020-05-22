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
		// TODO :: üũ �ݸ���
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

				// ù �浹�̶�� �ǹ�
				if ((*iterSrc)->CheckCollisionList(*iterDest)) {
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc);

					// Ŭ���̾�Ʈ�� ù �浹�� ó���ش޶�� ����س��� �Լ� ��
					(*iterSrc)->CallFunction(CS_ENTER, *iterDest,
						fDeltaTime);
					(*iterSrc)->CallFunction(CS_ENTER, *iterSrc,
						fDeltaTime);
				}
				else { // �̹� ������Ʈ���� �����ִ�	
					(*iterSrc)->CallFunction(CS_STAY, *iterDest,
						fDeltaTime);
					(*iterSrc)->CallFunction(CS_STAY, *iterSrc,
						fDeltaTime);
				}
			}
			// �浹���¿������� �ش� ������ ���Լ��� �� ������Ʈ�� �浹���¿��� �����.
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
