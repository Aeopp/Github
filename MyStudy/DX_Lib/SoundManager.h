#pragma once
#include "Std.h"
#include "fmod.hpp"
#include <unordered_map>
//struct Sound {
//	FMOD::System* F_System = nullptr;
//	FMOD::Sound* F_Sound = nullptr;
//	FMOD::Channel* F_Channel = nullptr;
//	uint32_t unique_number = -1;
//
//	void Pause() {
//		bool isplay = false;
//		if (F_Channel != nullptr) {
//			F_Channel->isPlaying(&isplay);
//
//			if (isplay == true) {
//				bool is_pause = false;
//				F_Channel->getPaused(&is_pause);
//				F_Channel->setPaused(!is_pause);
//			}
//		}
//	};
//	bool Load(FMOD::System* P_System, const std::wstring& Fullpath, const std::wstring& filename) {
//		if (P_System == nullptr)
//			return false;
//
//		F_System = P_System;
//		FMOD_RESULT HR;
//
//		std::string convert_string(std::begin(Fullpath), std::end(Fullpath));
//		auto* SoundHandle = F_Sound;
//
//		HR = F_System->createSound
//		(convert_string.c_str(), FMOD_DEFAULT, 0, &SoundHandle);
//
//		if (HR != FMOD_OK)
//			return false;
//
//		ReadKey = filename;
//		F_Sound->getLength(&Length, FMOD_TIMEUNIT_MS);
//		F_Channel->setVolume(Volume/*0.5f default*/);
//
//		return true;
//	};
//};

class SoundManager : public Singleton<SoundManager>
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
};

#define GetSound SoundManager::GetInstance()
