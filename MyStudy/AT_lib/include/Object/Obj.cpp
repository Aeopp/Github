#include "Obj.h"

CObj::CObj() {};

CObj::~CObj()
{
	SAFE_DELETE(m_pScene);
	SAFE_DELETE(m_pLayer); 
}
CObj::CObj(const CObj & Obj)
{
	*this = Obj;
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

void CObj::ErasePrototype()
{
	Safe_Delete_Map(m_mapPrototype);
}
void CObj::ErasePrototype(const wstring& strTag)
{
	auto iter = m_mapPrototype.find(strTag);
	if (!iter->second) {
		return; 
	}
	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter); 
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
}

CObj* CObj::CreateCloneObj(const wstring& strTagPrototypeKey, const wstring& strTag, class CLayer* pLayer)
{
	CObj* pProto = FindPtototype(strTagPrototypeKey);

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

CObj* CObj::FindPtototype(const wstring& strKey)
{
	auto iter = m_mapPrototype.find(strKey); 
	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}
