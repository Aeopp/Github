#pragma once
#include <map>
#include <string>
#include <memory>
#include "Sound.h"
#include "manager_Interface.h"
#include "Util.h"

class SoundMgr : private manager_Interface<SoundMgr>
{
public:
	using Key_Type = std::wstring; 
	using Sound_ptr = std::unique_ptr<Sound>; 
	friend class std::unique_ptr<SoundMgr>;
	friend struct std::unique_ptr<SoundMgr>::deleter_type; 
	friend class util;

	SoundMgr(const SoundMgr&) = delete;
	SoundMgr& operator=(const SoundMgr&) = delete; 
	SoundMgr(SoundMgr&&) noexcept = delete;
	SoundMgr& operator=(SoundMgr&&) noexcept = delete;

	bool Load(Key_Type LoadName)noexcept;
	bool clear()noexcept; 
	// unique_ptr 로 반환함 사용자는 Sound 사용이후 재사용을 원한다면 다시
	// 삽입해야함 
	Sound_ptr getSoundPtr(const Key_Type& Param_key);
private: 
	SoundMgr() = default;
	virtual ~SoundMgr() noexcept = default;
	std::map</*const */Key_Type, Sound_ptr> Map;
};

