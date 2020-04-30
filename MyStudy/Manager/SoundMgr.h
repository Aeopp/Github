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
	bool clear()noexcept;
	bool Init()noexcept(false);
	bool Frame();
	bool Render(); 

	// unique_ptr �� ��ȯ�� ����ڴ� Sound ������� ������ ���Ѵٸ� �ٽ�
	// �����ؾ��� 
	Sound_ptr getSound(const Key_Type& Param_key);
private: 
	SoundMgr();
	virtual ~SoundMgr() noexcept;
	std::map</*const */Key_Type, Sound_ptr> Map;

	FMOD::System* F_System; 
};

