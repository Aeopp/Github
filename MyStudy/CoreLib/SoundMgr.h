#pragma once
#include <map>
#include <memory>
#include <string>
#include "manager_Interface.h"
#include "Sound.h"
#include "Util.h"
#include "Type_Aliases.h"
#include <optional>

// TODO :: FMOD::System �������� ã�Ƽ� 
// TODO :: ������ ���� 
class SoundMgr : private manager_Interface<SoundMgr>
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

	// ����ڴ� Sound ��ü ���� �������� ���Ѵ�.
	std::weak_ptr<Sound> getSound(const Key_Type& Param_key);
	
	// ��������� ��� ���� ������̴� ������ �����ְ� Key �� �ش��ϴ� ������ ���
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const const Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
private:
	// ���� ���ǿ� �޼ҵ�
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

