#include "SoundManager.h"

bool	SoundManager::Init()
{
	FMOD_RESULT hr;
	hr = FMOD::System_Create(&FModSystem);
	if (hr != FMOD_OK) return false;
	hr = FModSystem->init(32, FMOD_INIT_NORMAL, 0);
	if (hr != FMOD_OK) return false;
	return true;
}
bool	SoundManager::Frame()             
{
	for (auto& [Key,CurrentSound]: Sounds) {
		CurrentSound->Frame();
	};
	FModSystem->update();
	return true;
}
bool	SoundManager::Render()
{
	for (auto& [Key, CurrentSound] : Sounds) {
		CurrentSound->Render();
	};
	return true;
}


int		SoundManager::Load(tstring Fullpath)
{
	// ../../../data/sound/xx.mp3
	tstring szFileName = Utility::PathDelete(Fullpath);
	
	for (auto& [Key, CurrentSound] : Sounds) {
		if (CurrentSound->m_csName == szFileName) {
			return Key;
		}
	}
	TSound* pData = nullptr;
	SAFE_NEW(pData, TSound);
	pData->Init();
	pData->m_csName = szFileName;
	if (pData->Load(Fullpath, FModSystem))
	{
		Sounds.insert(make_pair(++m_iCurIndex, pData));
		return m_iCurIndex;
	}
	SAFE_DEL(pData);
	return -1;
}

TSound* SoundManager::GetPtr(int iIndex)
{
	TItor iter = Sounds.find(iIndex);
	if (iter != Sounds.end())
	{
		return iter->second;
	}
	return nullptr;
}
bool SoundManager::Release()
{
	TSound* pData = nullptr;
	for (TItor iter = Sounds.begin();
		 iter != Sounds.end();
			iter++)
	{
		pData = iter->second;
		pData->Release();
		SAFE_DEL(pData);
	}
	Sounds.clear();
	FModSystem->close();
	FModSystem->release();
	return true;
}
SoundManager::SoundManager()
	: DefaultPath{ L"../../../Data/Sound/" }
{
	m_iCurIndex = 0;
	FModSystem = nullptr;
	Init();
}
SoundManager::~SoundManager()
{
	Release();
}