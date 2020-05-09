#include "SoundManager.h"


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
	
	if (auto FindIterator = Sounds.lower_bound(FileName); 
		FindIterator!=std::end(Sounds)&&FindIterator->first == FileName) {
		return FindIterator->second;
	}
	else if (auto NewSound = std::make_shared<Sound>(Sound( Fullpath,FModSystem ));
		NewSound){
		return Sounds.try_emplace(FindIterator, std::move(FileName), std::move(NewSound))->second;
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
bool SoundManager::Clear()noexcept
{
	Sounds.clear();
	return true;
}
SoundManager::SoundManager()
	: DefaultPath{ L"../../../Data/Sound/" }
{
	FMOD_RESULT ModResult;
	FMOD::System* IninFmodSystem;
	ModResult = FMOD::System_Create(&IninFmodSystem);
	if (ModResult != FMOD_OK) throw std::exception(Debug::Log("ModResult != FMOD_OK"));
	ModResult = IninFmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	if (ModResult != FMOD_OK) throw std::exception(Debug::Log("ModResult != FMOD_OK"));

	FModSystem = std::shared_ptr<FMOD::System>(IninFmodSystem,[](FMOD::System* FmodSystem) 
	{FmodSystem->close(); FmodSystem->release();});
}
SoundManager::~SoundManager()noexcept
{
	
}