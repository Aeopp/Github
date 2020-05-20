#include "ResourcesManager.h"
#include "Texture.h"

DEFINTION_SINGLE(CResourcesManager)

CResourcesManager::CResourcesManager() {
}

CResourcesManager::~CResourcesManager() {
	Safe_Delete_Map(m_mapTexture);
}

bool CResourcesManager::Init(HINSTANCE hInst, HDC hDC)
{
	m_hDC = hDC;
	m_hInst = hInst; 
	return true ;
}

CTexture* CResourcesManager::LoadTexture(const wstring& strKey,
	const wchar_t* pFileName,
	const wstring& strPathKey){
	CTexture * pTexture = FindTexture(strKey);

	if (pTexture)
		return pTexture;

	pTexture = new CTexture;

	if (!pTexture->LoadTexture(m_hInst,
		m_hDC,
		strKey, pFileName, strPathKey)) {
		SAFE_RELEASE(pTexture);
		return nullptr;
	}
	pTexture->AddRef();
	m_mapTexture.insert(std::make_pair(strKey, pTexture));
	return pTexture;
}

CTexture* CResourcesManager::FindTexture(const wstring& strKey)
{
	auto iter = m_mapTexture.find(strKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	iter->second->AddRef();
	return iter->second;
}
