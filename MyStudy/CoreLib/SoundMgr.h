#pragma once
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
	typename SoundMgr::Sound_ptr get_sound_ptr(const Key_Type& Param_key)&;
	SoundMgr();
	virtual ~SoundMgr() noexcept;
	std::map</*const */Key_Type,Sound_ptr> Map;
	std::weak_ptr<Sound> Current_Bgm;
	FMOD::System* F_System; 
};
