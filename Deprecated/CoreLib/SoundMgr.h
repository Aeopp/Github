#pragma once
#include <map>
#include <memory>
#include <string>
#include "manager_Interface.h"
#include "Sound.h"
#include "Util.h"
#include "Type_Aliases.h"
#include <optional>

// TODO :: FMOD::System 생성지점 찾아서 
// TODO :: 딜리터 세팅 
class SoundMgr : public manager_Interface<SoundMgr>
{
public:
	using Sound_ptr = std::shared_ptr<Sound>; 
	friend class std::unique_ptr<SoundMgr>;
	friend struct std::unique_ptr<SoundMgr>::deleter_type;
	friend class util;

	SoundMgr(const SoundMgr&) = delete;
	SoundMgr& operator=(const SoundMgr&) = delete; 
	SoundMgr(SoundMgr&&) noexcept = delete;
	SoundMgr& operator=(SoundMgr&&) noexcept = delete;

	std::optional<typename SoundMgr::Sound_ptr> Load(const Key_Type& FullPath)noexcept(false);
	bool Clear_Implementation()noexcept;
	bool Init_Implementation()noexcept(false);
	bool Frame_Implementation();
	bool Render_Implementation();

	// 사용자는 Sound 객체 수명에 관여하지 못한다.
	std::weak_ptr<Sound> getSound(const Key_Type& Param_key);
	
	// 배경음악일 경우 기존 재생중이던 음악을 멈춰주고 Key 에 해당하는 음악을 재생
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const  Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
private:
	// 구현 편의용 메소드
	std::optional<typename SoundMgr::Sound_ptr> get_sound_ptr(const Key_Type& Param_key)&;
	
	SoundMgr();
	virtual ~SoundMgr() noexcept;
	
	std::map<Key_Type,Sound_ptr> Map;
	std::weak_ptr<Sound> Current_Bgm;
	HFMod_System F_System; 
};

SoundMgr::SoundMgr() :F_System{ nullptr }
{
	Init_Implementation();
};

SoundMgr::~SoundMgr() noexcept
{
	Clear_Implementation();
};

