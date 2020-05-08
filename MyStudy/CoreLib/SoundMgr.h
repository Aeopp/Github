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

	// ����ڴ� Sound ��ü ���� �������� ���Ѵ�.
	std::weak_ptr<Sound> getSound(const Key_Type& Param_key);
	
	// ��������� ��� ���� ������̴� ������ �����ְ� Key �� �ش��ϴ� ������ ���
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const  Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
	void SetDefaultPath(const ReadType& SetPath); 
private:
	// ���� ���ǿ� �޼ҵ�
	std::weak_ptr<Sound > get_sound_ptr(const Key_Type& Param_key)&;
	std::map<Key_Type, std::shared_ptr<Sound> > Map;
	ReadType DefaultPath;
	std::weak_ptr<Sound> Current_Bgm;
	FMOD::System* F_System; 
};


