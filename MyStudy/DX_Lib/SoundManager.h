#pragma once
#include "Std.h"
#include "fmod.hpp"
#include <unordered_map>

class SoundManager : public SingleTon<SoundManager>
{
public :
	using SoundType = std::tuple<FMOD::System*, FMOD::Sound*, FMOD::Channel*>;
	std::unordered_map<std::string,SoundType> Sounds;
	static inline constexpr float DefaultVolume = 0.5f; 
	FMOD::System* FMOD_System = nullptr;
public :
	bool Play(const std::string& SoundKey,
		bool IsBgm=false);
	bool Load( std::string FullPath);
	bool Init();
	bool Frame();
	bool Release();
private:
	std::string CurrentBgmKey;
	DECLARE_SINGLETON(SoundManager)
};
