#include "CScene.h"
#include "Layer.h"
#include "../Object/Obj.h"
#include <algorithm>
CScene::CScene()
{
	CLayer* pLayer = CreateLayer(L"UI",  INT_MAX);
	pLayer = CreateLayer(L"Default",1);
	pLayer = CreateLayer(L"Stage");
}

CScene::~CScene() noexcept
{
	ErasePrototype(); 
	Safe_Delete_VecList(m_LayerList);
}

CLayer* CScene::CreateLayer(const wstring& strTag, int iZOrder)
{
	CLayer* pLayer = new CLayer;

	pLayer->SetTag(strTag);
	pLayer->SetZOrder(iZOrder);
	pLayer->SetScene(this); 

	m_LayerList.push_back(pLayer);

	if (m_LayerList.size() >= 2) {
		m_LayerList.sort(CScene::LayerSort);
	}
	return  pLayer; 
}

CLayer* CScene::FindLayer(const wstring& strTag)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		if ((*iter)->GetTag() == strTag) {
			return *iter; 
		} 
	}
	return nullptr; 
}

bool CScene::Init()
{
	return true;
}

void CScene::Input(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()){
			++iter;
			continue; 
		}
		(*iter)->Input(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;  
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Update(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
	// 죽은 오브젝트와 살아있는 오브젝트를 분리
	// 분리한 이후 자료구조에서 오브젝트를 삭제하고 메모리를 해제한다.
	using ObjPtrType = decltype(CObj::m_ObjList)::value_type;
	// True //////iter->False 
	auto DieObject = std::stable_partition(std::begin(CObj::m_ObjList), std::end(CObj::m_ObjList),
		[](ObjPtrType findDeath) {
			return  (findDeath->GetLife()==true); });
	std::for_each(DieObject, std::end(CObj::m_ObjList), [](ObjPtrType Obj) {
		SAFE_DELETE(Obj); });
	CObj::m_ObjList.erase(DieObject, std::end(CObj::m_ObjList));

	/*for (auto iter = CObj::m_ObjList.begin(); iter != std::end(CObj::m_ObjList);
		) {
		if ((*iter)->GetLife() == false) {
			SAFE_DELETE(*iter);
			iter = CObj::m_ObjList.erase(iter);
		}
		else
			++iter; 
	}*/
	return 0; 
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->LateUpdate(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
	return 0;
}

void CScene::Collision(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Collision(fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ) {
		if (!(*iter)->GetEnable()) {
			++iter;
			continue;
		}
		(*iter)->Render(hDC, fDeltaTime);
		if (!(*iter)->GetLife()) {
			SAFE_DELETE((*iter));
			iter = m_LayerList.erase(iter);
			iterEnd = m_LayerList.end();
		}
		else ++iter;
	}
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2)
{
	//CLayer* pLayer = new CLayer;

	return pL1->GetZOrder() < pL2->GetZOrder(); 
}
void CScene::ErasePrototype()
{
	Safe_Release_Map(m_mapPrototype);
}
void CScene::ErasePrototype(const wstring& strTag)
{
	auto iter = m_mapPrototype.find(strTag);
	if (!iter->second) {
		return;
	}
	SAFE_RELEASE(iter->second);
	m_mapPrototype.erase(iter);
}


CObj* CScene::FindPtototype(const wstring& strKey)
{
	auto iter = m_mapPrototype.find(strKey);
	if (iter == m_mapPrototype.end())
		return nullptr;

	return iter->second;
}
