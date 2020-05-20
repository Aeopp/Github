#include "PathManager.h"

DEFINTION_SINGLE(CPathManager)

CPathManager::CPathManager() {};

CPathManager::~CPathManager() {};

bool CPathManager::Init()
{
	wchar_t strPath[MAX_PATH];  

	GetModuleFileName(NULL,strPath,
	MAX_PATH);

	for (int i = lstrlen(strPath) - 1; i >= 0; --i) {
		if (strPath[i] == '/' || strPath[i] == '\\') {
			memset(strPath + (i + 1), 0, sizeof(wchar_t) *
				(MAX_PATH - (i + 1)));
			break;
		}
	}

	m_mapPath.insert(std::make_pair
	(ROOT_PATH,strPath));

	if (!CreatePath(TEXTURE_PATH, L"Texture\\")) {
		return false; 
	}
	return true;
}

bool CPathManager::CreatePath(const wstring& strKey, const wchar_t* pPath, const wstring& strBaseKey)
{
	const wchar_t* pBasePath = FindPath(strBaseKey);

	wstring strPath;
	if (pBasePath) {
		strPath = pBasePath;
	}
	strPath += pPath;
	m_mapPath.insert(make_pair(strKey, strPath));

	return true;
}

const wchar_t* CPathManager::FindPath(const wstring& strKey)
{
	auto iter = m_mapPath.find(strKey);
	if (iter == m_mapPath.end()) {
		return nullptr;
	}
	return iter->second.c_str(); 
}
