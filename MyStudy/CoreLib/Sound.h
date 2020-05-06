#pragma once
#include "ObjectSuper.h"
#include <string>
//#include "fmod.h"
#include "fmod.hpp"
#include <algorithm>
#include <functional>
#include "Util.h"
#include "Convenience_function.h"

class Sound : public ObjectSuper 
{
public:
	using ReadType = std::wstring; 

	Sound();
	
	virtual bool Init()noexcept override;
	bool Render() const;
	virtual bool Clear()noexcept override;
	virtual bool Frame() override;
	// 1. 소멸자에서 clear 호출해주거나
	// 2. 클래스 사용측에서 clear 호출해주거나
	// 3. 스마트포인터에 딜리터 세팅해서 신경안쓰기
	virtual ~Sound();
	
	void Pause(); 
	void Stop();
	void SetMode(uint32_t mode_param = FMOD_LOOP_NORMAL); 
	bool inline isPlay() const&;

	
	bool Load(ReadType P_ReadType,FMOD::System*const P_System);
	bool Play();
	bool PlayEffect();

	void inline Volume_Up()&;
	void inline Volume_Down()&;

	inline typename Sound::ReadType getReadKey()const&;
private:
	void inline Volume_Impl(bool updown_tag)&;
	ReadType ReadKey;
	FMOD::System* F_System;
	FMOD::Sound* F_Sound;
	FMOD::Channel* F_Channel;
	
	float_t Volume;
	uint32_t Length;
	std::wstring played_time; 
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

inline typename Sound::ReadType Sound::getReadKey()const&
{
	return ReadKey; 
}