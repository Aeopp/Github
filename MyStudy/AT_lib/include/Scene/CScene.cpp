#include "CScene.h"
#include "Layer.h"
CScene::CScene()
{
	CLayer* pLayer = CreateLayer("Default",  INT_MAX);
	//pLayer->CreateLayer("Default");
}

CScene::~CScene() noexcept
{
	Safe_Delete_VecList(m_LayerList);
}

CLayer* CScene::CreateLayer(const string& strTag, int iZOrder)
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

CLayer* CScene::FindLayer(const string& strTag)
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

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		(*iter)->Input(fDeltaTime);
	}
}

int CScene::Update(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		(*iter)->Update(fDeltaTime);
	}
	return 0; 
}

int CScene::LateUpdate(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		(*iter)->LateUpdate(fDeltaTime);

	}return 0;
}

void CScene::Collision(float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		(*iter)->Collision(fDeltaTime);

	}
}

void CScene::Render(HDC hDC, float fDeltaTime)
{
	list<CLayer*>::iterator iter;
	list<CLayer*>::iterator iterEnd = m_LayerList.end();

	for (iter = m_LayerList.begin(); iter != iterEnd; ++iter) {
		(*iter)->Render(hDC,fDeltaTime);

	}
}

bool CScene::LayerSort(CLayer* pL1, CLayer* pL2)
{
	//CLayer* pLayer = new CLayer;

	return pL1->GetZOrder() < pL2->GetZOrder(); 
}


