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
	friend class std::unique_ptr<SoundMgr>;
	friend struct std::unique_ptr<SoundMgr>::deleter_type;
	friend class util;
	
	SoundMgr() :F_System{ nullptr }
	{
		Init();
	};

	virtual ~SoundMgr() noexcept
	{
		Clear();
	};
	SoundMgr(const SoundMgr&) = delete;
	SoundMgr& operator=(const SoundMgr&) = delete; 
	SoundMgr(SoundMgr&&) noexcept = delete;
	SoundMgr& operator=(SoundMgr&&) noexcept = delete;

	std::weak_ptr<Sound> Load(const Key_Type& FullPath)noexcept(false);
	bool Clear()noexcept;
	bool Init()noexcept;
	bool Frame();
	bool Render();

	// 사용자는 Sound 객체 수명에 관여하지 못한다.
	std::weak_ptr<Sound> getSound(const Key_Type& Param_key);
	
	// 배경음악일 경우 기존 재생중이던 음악을 멈춰주고 Key 에 해당하는 음악을 재생
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const  Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
	void SetDefaultPath(const ReadType& SetPath); 
private:
	// 구현 편의용 메소드
	std::weak_ptr<Sound > get_sound_ptr(const Key_Type& Param_key)&;
	std::map<Key_Type, std::shared_ptr<Sound> > Map;
	ReadType DefaultPath;
	std::weak_ptr<Sound> Current_Bgm;
	FMOD::System* F_System; 
};


