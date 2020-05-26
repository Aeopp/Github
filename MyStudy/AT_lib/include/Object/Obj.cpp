#include "Obj.h"
#include "../Scene/CScene.h"
#include "../Scene/CSceneManager.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Collision/Colinder.h"
#include "../CCore.h"
CObj::CObj() :
	m_pTexture{ nullptr }
{};

// Memory Leak Dected!! 
CObj::~CObj()
{
	Safe_Release_VecList(m_ColliderList);
	SAFE_RELEASE(m_pTexture);
 	/*SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pLayer); */
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;
	if (m_pTexture) {
		m_pTexture->AddRef();
	}

	m_ColliderList.clear();
	list<CCollider*>::const_iterator iter;
	list<CCollider*>::const_iterator iterEnd = Obj.m_ColliderList.end();
	for (iter = Obj.m_ColliderList.begin(); iter != iterEnd; ++iter) {
		CCollider* pColl = (*iter)->Clone();
		pColl->SetObj(this);
		m_ColliderList.push_back(pColl);
	}
	/*for (auto Object : Obj.m_CollinderList){
		auto* pCollider = Object->Clone();
		pCollider->SetObj(this);
		m_CollinderList.push_back(pCollider);
	}*/
}

void CObj::AddObj(CObj* pObj)
{
	pObj->AddRef(); 
	m_ObjList.push_back(pObj);
}

CObj* CObj::FindObject(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end() ;

	for (iter = m_ObjList.begin(); iter != iterEnd;++iter) {
		if ((*iter)->GetTag() == strTag) {
			(*iter)->AddRef();
			return *iter;  
		}
	}
	return nullptr;
}

void CObj::EraseObj(CObj* pObj)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;){
		if (*iter == pObj) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter); 
			return; 
		}
		else
			++iter; 
	}
}

void CObj::EraseObj(const wstring& strTag)
{
	list<CObj*> ::iterator iter;
	list<CObj*> ::iterator iterEnd = m_ObjList.end();

	for (iter = m_ObjList.begin(); iter != iterEnd;) {
		if ((*iter)->GetTag() == strTag) {
			SAFE_RELEASE((*iter));
			iter = m_ObjList.erase(iter);
			return;
		}
		else
			++iter;
	}
}

void CObj::EraseObj()
{
	Safe_Release_VecList(m_ObjList);
}

void CObj::SetTexture(CTexture* pTexture){
	SAFE_RELEASE(m_pTexture);
	m_pTexture = pTexture;
	if (pTexture)
		pTexture->AddRef();
}

void CObj::SetTexture(const wstring& strKey, const wchar_t* pFileName, const wstring& strPathKey){
		SAFE_RELEASE(m_pTexture);
		m_pTexture = GET_SINGLE(CResourcesManager)->LoadTexture(strKey,pFileName,strPathKey);
}

void CObj::Input(float fDeltaTime)
{
	for (auto iter = std::begin(m_ColliderList); iter != std::end(m_ColliderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
		}
		else ++iter;
	}
}

int CObj::Update(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter; 
			continue; 
		}

		(*iter)->Update(fDeltaTime);
		
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter; 
	}
	return 0;
	/*list<CColliderRect*>::iterator iter;
	list<CColliderRect*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd;) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	return 0;*/

	/*for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		){
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}
	return 0;*/
}

int CObj::LateUpdate(float fDeltaTime)
{
	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->LateUpdate(fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}
	return 0;
}

void CObj::Collision(float fDeltaTime)
{

	/*for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}*/

	//for (auto iter = std::begin(HitList); iter != std::end(HitList); ++iter) {
	//	if (iter->second == ECOLLISION_STATE::Nothing) {
	//		//SAFE_RELEASE(iter->first);
	//		HitList.erase(iter);
	//	}
	//}
	for (auto iter = std::begin(HitList); iter != std::end(HitList); ++iter) {
		auto Target = iter->first;
		auto State = FindHitList(iter->first);

		if (State.second != ECOLLISION_STATE::Keep &&
			State.second != ECOLLISION_STATE::First) {

			auto Test = Target->GetTag() + m_strTag.c_str();
			MessageBox(NULL, Test.c_str(), L"Release !! ", MB_OK);
		}
	}
}

void CObj::Hit(CObj* const Target, float fDeltaTime)
{
	if (m_strTag == L"Stage") {
		return;
	};

	auto State =FindHitList(Target);

	// ����Ʈ���� ã�� �������Ƿ� ó�� �浹
	if (State.second == ECOLLISION_STATE::Nothing) {
		MessageBox(NULL, Target->GetTag().c_str(), m_strTag.c_str(), MB_OK);
		AddHitList(Target, ECOLLISION_STATE::First);
	}
	// ����Ʈ���� ã�Ҵ� �浹 ������
	else if (State .second== ECOLLISION_STATE::First) {
		MessageBox(NULL, Target->GetTag().c_str(), m_strTag.c_str(), MB_OK);
		State.second = ECOLLISION_STATE::Keep;
	}
	else {
		auto Test  = Target->GetTag() + m_strTag.c_str();
		MessageBox(NULL,Test.c_str(), L"Release !! ", MB_OK);
	}


	//// ����Ʈ���� ã�Ҵ� �浹 ������
	//else if (State.second == ECOLLISION_STATE::First ||
	//	State.second == ECOLLISION_STATE::Keep){

	//	State.second = ECOLLISION_STATE::Release;
	//}
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot; 
		tPos -= GET_SINGLE(CCamera)->GetPos();
		/*Rectangle(hDC, tPos.x, tPos.y, tPos.x + m_tSize.x, tPos.y + m_tSize.y);
		*/

		if (m_pTexture->GetColorKeyEnable()==true) {
			TransparentBlt(hDC, tPos.x, tPos.y, m_tSize.x,
				m_tSize.y, m_pTexture->GetDC(), 0, 0,
				m_tSize.x, m_tSize.y, m_pTexture->GetColorKey());
		}
		else {
			BitBlt(hDC, tPos.x, tPos.y,
				m_tSize.x, m_tSize.y, m_pTexture->GetDC(), 0, 0,
				SRCCOPY);
		}
	}

	list<CCollider*>::iterator iter;
	list<CCollider*>::iterator iterEnd = m_ColliderList.end();

	for (iter = m_ColliderList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}

		(*iter)->Render(hDC,fDeltaTime);

		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_ColliderList.erase(iter);
			iterEnd = m_ColliderList.end();
		}
		else
			++iter;
	}

	//list<CColliderRect*>::iterator iter;
	//list<CColliderRect*>::iterator iterEnd = m_ColliderList.end();

	//for (iter = m_ColliderList.begin(); iter != iterEnd;) {
	//	if (!(*iter)->GetEnable()) {
	//		++iter;
	//		continue;
	//	}
	//	(*iter)->Render(hDC,fDeltaTime);
	//	if (!(*iter)->GetLife()) {
	//		SAFE_RELEASE((*iter));
	//		iter = m_ColliderList.erase(iter);
	//		iterEnd = m_ColliderList.end();
	//	}
	//	else
	//		++iter;
	//}

}

CObj* CObj::CreateCloneObj(const wstring& strTagPrototypeKey, const wstring& strTag, class CLayer* pLayer)
{
	CObj* pProto = CScene::FindPtototype(strTagPrototypeKey);

	if (!pProto)
		return nullptr;
	 
	CObj* pObj = pProto->Clone();
	pObj->SetTag(strTag);
	if (pLayer) {
		pLayer->AddObject(pObj); 
	}
	AddObj(pObj);
	return pObj;
}
