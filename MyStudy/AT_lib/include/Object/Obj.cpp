#include "Obj.h"
#include "../Scene/CScene.h"
#include "../Scene/CSceneManager.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
#include "../Collision/Colinder.h"
CObj::CObj() :
	m_pTexture{ nullptr }
{};

// Memory Leak Dected!! 
CObj::~CObj()
{
	Safe_Release_VecList(m_CollinderList);
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

	m_CollinderList.clear();
	for (auto Object : Obj.m_CollinderList){
		auto* pCollider = Object->Clone();
		m_CollinderList.emplace_back(pCollider);
	}
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
	for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}
}

int CObj::Update(float fDeltaTime)
{
	for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
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
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
	for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision( fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot; 
		tPos -= GET_SINGLE(CCamera)->GetPos();
		Ellipse(hDC, tPos.x, tPos.y, tPos.x + m_tSize.x, tPos.y + m_tSize.y);
		

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

	for (auto iter = std::begin(m_CollinderList); iter != std::end(m_CollinderList);
		) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Render(hDC,fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_RELEASE((*iter));
			iter = m_CollinderList.erase(iter);
		}
		else ++iter;
	}
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
