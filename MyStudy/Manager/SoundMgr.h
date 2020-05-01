#pragma once
#include <fmod.h>
#include <fmod_errors.h>
#include <fmod.hpp>
#include <map>
#include <memory>
#include <string>
#include "manager_Interface.h"
#include "Sound.h"
#include "Util.h"

class SoundMgr : private manager_Interface<SoundMgr>
{
public:
	using Key_Type = std::wstring; 
	using Sound_ptr = std::shared_ptr<Sound>; 
	friend class std::unique_ptr<SoundMgr>;
	friend struct std::unique_ptr<SoundMgr>::deleter_type;
	friend class util;

	SoundMgr(const SoundMgr&) = delete;
	SoundMgr& operator=(const SoundMgr&) = delete; 
	SoundMgr(SoundMgr&&) noexcept = delete;
	SoundMgr& operator=(SoundMgr&&) noexcept = delete;

	bool Load(Key_Type LoadName)noexcept(false); 
	bool Clear()noexcept;
	bool Init()noexcept(false);
	bool Frame();
	bool Render();

	// 사용자는 Sound 객체 수명에 관여하지 못한다.
	std::weak_ptr<Sound> getSound(const Key_Type& Param_key);
	
	// 배경음악일 경우 기존 재생중이던 음악을 멈춰주고 Key 에 해당하는 음악을 재생
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const const Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
private:
	// 구현 편의용 메소드
	typename SoundMgr::Sound_ptr get_sound_ptr(const Key_Type& Param_key)&;
	SoundMgr();
	virtual ~SoundMgr() noexcept;
	std::map</*const */Key_Type, Sound_ptr> Map;
	std::weak_ptr<Sound> Current_Bgm;
	FMOD::System* F_System; 
};


