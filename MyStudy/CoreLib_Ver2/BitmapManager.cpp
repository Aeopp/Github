#include "BitmapManager.h"

bool	TBitmapMgr::Init()
{
	return true;
}
bool	TBitmapMgr::Frame()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Frame();
	}
	return true;
}
bool	TBitmapMgr::Render()
{
	for (int iSound = 0; iSound < m_Map.size(); iSound++)
	{
		m_Map[iSound + 1]->Render();
	}
	return true;
}


int		TBitmapMgr::Load(HDC hScreenDC, tstring szLoadName)
{
	// ../../../data/sound/xx.mp3
	TCHAR szDirve[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDirve, szDir, szName, szExt);
	tstring szFileName = szName;
	szFileName += szExt;
	for (TItor itor = m_Map.begin();
		itor != m_Map.end(); itor++)
	{
		TBitmap* pData = (*itor).second;
		if (pData->m_csName == szFileName)
		{
			return (*itor).first;
		}
	}

	TBitmap* pData = nullptr;
	SAFE_NEW(pData, TBitmap);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(hScreenDC,szLoadName))
	{
		m_Map.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}

TBitmap* TBitmapMgr::GetPtr(int iIndex)
{
	TItor iter = m_Map.find(iIndex);
	if (iter != m_Map.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool TBitmapMgr::Release()
{
	TBitmap* pData = nullptr;
	for (TItor iter = m_Map.begin();
		iter != m_Map.end();
		iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	m_Map.clear();
	return true;
}
TBitmapMgr::TBitmapMgr()
{
	m_iCurIndex = 0;
	m_csDefaultPath = L"../../../Data/Bitmap/";
	Init();
}
TBitmapMgr::~TBitmapMgr()
{
	Release();
}