#include "Obj.h"
#include "../Scene/CScene.h"
#include "../Scene/CSceneManager.h"
#include "../Resources/ResourcesManager.h"
#include "../Resources/Texture.h"
#include "../Core/Camera.h"
CObj::CObj() :
	m_pTexture{ nullptr }
{};

// Memory Leak Dected!! 
CObj::~CObj()
{
	SAFE_RELEASE(m_pTexture);
 	/*SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pLayer); */
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;
	if (m_pTexture)
		m_pTexture->AddRef();
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

}

int CObj::Update(float fDeltaTime)
{
	return 0;
}

int CObj::LateUpdate(float fDeltaTime)
{
	return 0;
}

void CObj::Collision(float fDeltaTime)
{
}

void CObj::Render(HDC hDC, float fDeltaTime)
{
	if (m_pTexture) {
		POSITION tPos = m_tPos - m_tSize * m_tPivot; 
		tPos -= GET_SINGLE(CCamera)->GetPos();
		//Ellipse(hDC, tPos.x, tPos.y, tPos.x + m_tSize.x, tPos.y + m_tSize.y);
		

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
