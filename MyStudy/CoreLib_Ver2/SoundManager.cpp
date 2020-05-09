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


std::weak_ptr<Sound>	SoundManager::Load(tstring Fullpath)
{
	// ../../../data/sound/xx.mp3
	tstring FileName = Utility::PathDelete(Fullpath);

	for (auto& [Key, CurrentSound] : Sounds) {
		if (CurrentSound->FileName == FileName) {
			return CurrentSound;
		}
	}
	auto NewSound = std::make_shared<Sound>(FileName);
	if (NewSound->Load(Fullpath, FModSystem)) {
		Sounds.try_emplace(FileName,NewSound);
		return NewSound;
	}
}

std::weak_ptr<Sound> SoundManager::GetSound(const tstring& Key)
{
	if (auto FindIterator = Sounds.find(Key);
		FindIterator != std::end(Sounds)){
		return FindIterator->second;
	}
	else {
		return {};
	}
}
bool SoundManager::Release()
{
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