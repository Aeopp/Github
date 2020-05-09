#pragma once
#include "Sound.h"
class SoundManager : public SingleTon<SoundManager>
{
	friend class SingleTon<SoundManager>;
private:
	std::map<tstring,std::shared_ptr<Sound>>  Sounds;
	std::shared_ptr<FMOD::System>			FModSystem;
public:
	const tstring			DefaultPath;
public:
	bool	Clear()noexcept;
	bool	Frame();
	bool	Render();
	std::weak_ptr<Sound> Load(tstring Fullpath);
	std::weak_ptr<Sound> GetSound(const tstring& Key);
private:
	SoundManager();
public:
	~SoundManager()noexcept;
	SoundManager(SoundManager&&)noexcept = delete;
	SoundManager& operator=(SoundManager&&)noexcept = delete;
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
};
#define GetSoundManager SoundManager::Instance()