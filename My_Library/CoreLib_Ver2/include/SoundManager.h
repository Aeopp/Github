#pragma once
#include "Sound.h"
class SoundManager : public SingleTon<SoundManager>
{
	friend class SingleTon<SoundManager>;
private:
	int32_t					m_iCurIndex;
	std::map<tstring,std::shared_ptr<Sound>>  Sounds;
	FMOD::System*			FModSystem;
	const tstring			DefaultPath;
public:
	typedef std::map<int, Sound*>::iterator TItor;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	std::weak_ptr<Sound> Load(tstring szName);
	std::weak_ptr<Sound> GetSound(const tstring& Key);
private:
	SoundManager();
public:
	~SoundManager();
};
#define I_SoundMgr SoundManager::Instance()