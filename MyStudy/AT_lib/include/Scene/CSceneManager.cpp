#include "CSceneManager.h"

DEFINTION_SINGLE(CSceneManager) 

CSceneManager::CSceneManager()
	:m_pScene(nullptr) 
{
}

CSceneManager::~CSceneManager()
{
	SAFE_DELETE(m_pScene);
	/*DESTROY_SINGLE(CSceneManager);*/
}

bool CSceneManager::Init()
{
	CreateScene<CIngameScene>(SC_CURRENT);



	return true; 
}

void CSceneManager::Input(float fDeltaTime)
{
	m_pScene->Input(fDeltaTime); 
}

int CSceneManager::Update(float fDeltaTime)
{
	m_pScene->Update(fDeltaTime);

	return 0;
}

int CSceneManager::LateUpdate(float fDeltaTime)
{
	m_pScene->LateUpdate(fDeltaTime);

	return 0;
}

void CSceneManager::Collision(float fDeltaTime)
{
	m_pScene->Collision(fDeltaTime);

}

void CSceneManager::Render(HDC hDC, float fDeltaTime)
{
	m_pScene->Render(hDC,fDeltaTime);

}

