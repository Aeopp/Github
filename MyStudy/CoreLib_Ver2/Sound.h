#pragma once
#include "Object.h"
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>
class Sound : public TBaseObject
{
private:	
	FMOD::System*	m_pSystem;
	FMOD::Sound*	m_pSound;
	FMOD::Channel*	m_pChannel;
public:
	tstring			FileName;
	float			m_fVolume;
	unsigned int	m_msLength;
	TCHAR			m_csBuffer[256];
public:
	virtual bool	Init()	;		// 초기화
	virtual bool	Frame()	;	// 계산
	virtual bool	Render()	;	// 드로우
	virtual bool	Release()	;	// 소멸
public:
	void	Paused();
	void	Stop();
	void	VolumeUp();
	void	VolumeDown();
	void	SetMode(DWORD dwMode=FMOD_LOOP_NORMAL);
public:
	bool	Load(	tstring szName,
					FMOD::System* pSystem);
	void	Play();
	void	PlayEffect();
public:
	Sound(tstring FileName);
	virtual ~Sound();
};

