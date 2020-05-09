#pragma once
#include "Sound.h"
class SoundManager : public SingleTon<SoundManager>
{
	friend class SingleTon<SoundManager>;
private:
	int32_t					m_iCurIndex;
	std::map<int, TSound*>  Sounds;
	FMOD::System*			FModSystem;
	const tstring			DefaultPath;
public:
	typedef std::map<int, TSound*>::iterator TItor;
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();
	int		Load(tstring szName);
	TSound* GetPtr(int iIndex);
private:
	SoundManager();
public:
	~SoundManager();
};
#define I_SoundMgr SoundManager::Instance()