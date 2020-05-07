#pragma once
#include "ObjectSuper.h"
#include <string>
#include "fmod.hpp"
#include <algorithm>
#include "Util.h"
#include "Convenience_function.h"

// TODO::Sound <-> Manager Dependency names...
using HFMod_System = std::shared_ptr<FMOD::System>;
using HFMod_Sound = std::shared_ptr<FMOD::Sound>;
using HFMod_Channel = std::shared_ptr<FMOD::Channel>;

class Sound : public ObjectSuper
{
public:
	Sound();
	bool Frame();
	bool inline Init()      noexcept override;
	bool inline Render()override;
	bool inline Clear()      noexcept override;
	// 1. 소멸자에서 clear 호출해주거나
	// 2. 클래스 사용측에서 clear 호출해주거나
	// 3. 스마트포인터에 딜리터 세팅해서 신경안쓰기
	virtual ~Sound();
	
	void Pause(); 
	void inline Stop();
	void inline SetMode(uint32_t mode_param = FMOD_LOOP_NORMAL);
	bool inline isPlay() const&;
	
	bool Load(HFMod_System P_System,const std::wstring& Fullpath,const std::wstring& filename);
	bool Play();
	bool PlayEffect();

	void inline Volume_Up()&;
	void inline Volume_Down()&;
	inline ReadType getReadKey()const&;
	ReadType ReadKey;
private:
	void inline Volume_Impl(bool updown_tag)&;
	
	HFMod_System F_System;
	HFMod_Sound F_Sound;
	HFMod_Channel F_Channel;
	
	float_t Volume;
	uint32_t Length;
	std::wstring played_time; 
};
void inline Sound::Stop() {

	F_Channel->stop();
}

void inline Sound::SetMode(uint32_t mode_param) {
	F_Sound->setMode(mode_param);
};
inline void Sound::Volume_Up()&{
	Volume_Impl(true); 
}

inline void Sound::Volume_Down()&{
	Volume_Impl(false);
}

inline void Sound::Volume_Impl(bool updown_tag)&{
	if (F_Channel == nullptr)
		throw std::exception(Debug::Log("F_Channel == nullptr").c_str());

	auto Delta = time::delta_sec;
	
	float_t L_Volume = 1.f;
	float_t change_width = 0.1f;
	
	if (updown_tag == false) 
		change_width *= -1; 

	F_Channel->getVolume(&L_Volume);  
	L_Volume = std::clamp(L_Volume + (change_width * Delta) , 0.0f,1.0f);
	F_Channel->setVolume(L_Volume); 
}

bool inline Sound::isPlay() const&{
	
	bool _Isplay{ false };
	
	if (F_Channel != nullptr)
		F_Channel->isPlaying(&_Isplay);
	
	return _Isplay; 
}

inline ReadType Sound::getReadKey()const&
{
	return ReadKey; 
}

Sound::Sound() :
	F_System{ nullptr },
	F_Sound{ nullptr },
	Volume{ 0.5f },
	Length{}
{
	Init();
};

Sound::~Sound()noexcept
{
	Clear();
};


bool inline Sound::Render()
{
	std::wcout << played_time << std::endl;
}

