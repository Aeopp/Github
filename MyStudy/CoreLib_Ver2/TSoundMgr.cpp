#include "TSoundMgr.h"

bool	TSoundMgr::Init()
{
	FMOD_RESULT hr;
	hr = FMOD::System_Create(&m_pSystem);
	if (hr != FMOD_OK) return false;
	hr = m_pSystem->init(32, FMOD_INIT_NORMAL, 0);
	if (hr != FMOD_OK) return false;
	return true;
}
bool	TSoundMgr::Frame()             
{
	for (int iSound=0;iSound< m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Frame();
	}
	m_pSystem->update();
	return true;
}
bool	TSoundMgr::Render()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Render();
	}
	return true;
}


int		TSoundMgr::Load(T_STR szLoadName)
{
	// ../../../data/sound/xx.mp3
	TCHAR szDirve[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDirve, szDir, szName, szExt);
	T_STR szFileName = szName;
	szFileName += szExt;
	for (TItor itor = m_Map.begin();
		itor != m_Map.end(); itor++)
	{
		TSound* pData = (*itor).second;
		if (pData->m_csName == szFileName)
		{
			return (*itor).first;
		}
	}

	TSound* pData = nullptr;
	SAFE_NEW(pData, TSound);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(szLoadName, m_pSystem))
	{
		m_Map.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}

TSound* TSoundMgr::GetPtr(int iIndex)
{
	TItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool TSoundMgr::Release()
{
	TSound* pData = nullptr;
	for (TItor iter = m_Map.begin();
		 iter != m_Map.end();
			iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	m_pSystem->close();
	m_pSystem->release();
	return true;
}
TSoundMgr::TSoundMgr()
{
	m_iCurIndex = 0;
	m_pSystem = nullptr;
	m_csDefaultPath = L"../../../Data/Sound/";
	Init();
}
TSoundMgr::~TSoundMgr()
{
	Release();
}