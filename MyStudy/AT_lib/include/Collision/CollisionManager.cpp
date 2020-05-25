#include "CollisionManager.h"
#include "../Object/Obj.h"
#include "../Collision/Colinder.h"

void CCollisionManager::AddObject(CObj* pObj)
{
	if (pObj->CheckCollider()) {
		m_CollisionList.push_back(pObj);
	}
}

void CCollisionManager::Collision(float fDeltaTime)
{
	if (m_CollisionList.size() < 2) {
		m_CollisionList.clear();
		return; 
	}

	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_CollisionList.end();
	--iterEnd;

	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
		list<CObj*> ::iterator iter1 = iter;
		++iter1; 
		list<CObj*> ::iterator iter1End = m_CollisionList.end();
		for (; iter1 != iter1End; ++iter1) {
			Collision(*iter, *iter1, fDeltaTime); 
		}
	}

	m_CollisionList.clear();
}

bool CCollisionManager::Collision(CObj* pSrc, CObj* pDest, float fDeltaTime)
{
	const list<CCollider*>* pSrcList = pSrc->GetColliderList();
	const list<CCollider*>* pDestList = pDest->GetColliderList();

	list<CCollider*>::const_iterator iterSrc;
	list<CCollider*>::const_iterator iterSrcEnd = pSrcList->end();

	list<CCollider*>::const_iterator iterDest;
	list<CCollider*>::const_iterator iterDestEnd = pDestList->end();

	bool bCollision = false; 

	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc){
		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest) 
		{
			if ((*iterSrc)->Collision(*iterDest))
			{
				bCollision = true;

				// �浹 ��Ͽ� �������Ƿ� ù �浹 (�浹�� ����)
				if (!(*iterSrc)->CheckCollisionList(*iterDest)) {
					// �浹 ���̺� �߰� �۾�
					(*iterSrc)->AddCollider(*iterDest);
					(*iterDest)->AddCollider(*iterSrc); 

					(*iterSrc)->CallFunction(CS_ENTER,
						*iterDest, fDeltaTime);

					(*iterDest)->CallFunction(CS_ENTER,
						*iterSrc, fDeltaTime);

				}
				 // ������ �浹 ������ �ִ� ��ü��
				else 
				{
					(*iterSrc)->CallFunction(CS_STAY,
						*iterDest, fDeltaTime);

					(*iterDest)->CallFunction(CS_STAY,
						*iterSrc, fDeltaTime);

				}
			}
			// ������ �浹 �̿����� ���� �����ӿ��� �浹 ���¸� ��� !! 
			else if((*iterSrc)->CheckCollisionList(*iterDest)) 
			{
				// �浹 ���̺� ����
				(*iterSrc)->EraseCollisionList(*iterDest);
				(*iterDest)->EraseCollisionList(*iterSrc); 

				(*iterSrc)->CallFunction(CS_LEAVE,
					*iterDest, fDeltaTime);

				(*iterDest)->CallFunction(CS_LEAVE,
					*iterSrc, fDeltaTime);

			}
		}
	}

	return bCollision;
}

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

//#include "CollisionManager.h"		
//#include "../Object/Obj.h"
//#include "Colinder.h"
//
//DEFINTION_SINGLE(CCollisionManager)
//
//CCollisionManager::CCollisionManager() {
//};
//
//CCollisionManager::~CCollisionManager() noexcept {
//};
//
//void CCollisionManager::AddObject(CObj* pObj)
//{
//	if (pObj->CheckCollider()) {
//		m_CollisionList.push_back(pObj);
//	}
//	else {
//
//	}
//}
//
//void CCollisionManager::Collision(float fDeltaTime)
//{
//	if (m_CollisionList.size() < 2) {
//		// TODO :: üũ �ݸ���
//		m_CollisionList.clear();
//		return;
//	};
//	list<CObj*>::iterator iter;
//	list<CObj*>::iterator iterEnd = m_CollisionList.end();
//	--iterEnd;
//	for (iter = m_CollisionList.begin(); iter != iterEnd; ++iter) {
//		list<CObj*>::iterator iter1 = iter;
//		++iter1;
//		list<CObj*>::iterator iter1End = m_CollisionList.end();
//	
//		for (; iter1 != iter1End; ++iter1) {
//			Collision(*iter, *iter1, fDeltaTime);
//		}
//	}
//
//	m_CollisionList.clear();
//}
//
//bool CCollisionManager::Collision(CObj* pSrc, CObj* pDest, float fDeltaTime)
//{
//	 list<CCollider*>* pSrcList = pSrc->GetColliderList();
//	 list<CCollider*>* pDestList = pDest->GetColliderList();
//
//	list<CCollider*>::iterator iterSrc;
//	list<CCollider*>::iterator iterSrcEnd = pSrcList->end();
//
//	list<CCollider*>::iterator iterDest;
//	list<CCollider*>::iterator iterDestEnd = pDestList->end();
//
//	bool bCollision = false; 
//
//	for (iterSrc = pSrcList->begin(); iterSrc != iterSrcEnd; ++iterSrc) {
//		for (iterDest = pDestList->begin(); iterDest != iterDestEnd; ++iterDest) {
//			if ((*iterSrc)->Collision(*iterDest)) {
//				bCollision = true; 
//
//				// ù �浹�̶�� �ǹ�
//				if ((*iterSrc)->CheckCollisionList(*iterDest)) {
//					(*iterSrc)->AddCollider(*iterDest);
//					(*iterDest)->AddCollider(*iterSrc);
//
//					// Ŭ���̾�Ʈ�� ù �浹�� ó���ش޶�� ����س��� �Լ� ��
//					(*iterSrc)->CallFunction(CS_ENTER, *iterDest,
//						fDeltaTime);
//					(*iterDest)->CallFunction(CS_ENTER, *iterSrc,
//						fDeltaTime);
//				}
//				else { // �̹� ������Ʈ���� �����ִ�	
//					(*iterSrc)->CallFunction(CS_STAY, *iterDest,
//						fDeltaTime);
//					(*iterDest)->CallFunction(CS_STAY, *iterSrc,
//						fDeltaTime);
//				}
//			}
//			// �浹���¿������� �ش� ������ ���Լ��� �� ������Ʈ�� �浹���¿��� �����.
//			else if((*iterSrc)->CheckCollisionList(*iterDest)){
//				(*iterSrc)->EraseCollisionList(*iterDest);
//				(*iterDest)->EraseCollisionList(*iterSrc);
//
//				(*iterSrc)->CallFunction(CS_LEAVE, *iterDest,
//					fDeltaTime);
//				(*iterDest)->CallFunction(CS_LEAVE, *iterSrc,
//					fDeltaTime);
//			}
//		}
//	}
//	return bCollision;
//}


