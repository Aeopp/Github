#include "Sound.h"
bool	Sound::Init()
{
	return true;
}
bool	Sound::Frame()
{
	if (m_pChannel == nullptr) return true;
	unsigned int ms;
	m_pChannel->getPosition(&ms, FMOD_TIMEUNIT_MS);
	ZeroMemory(m_csBuffer, sizeof(TCHAR) * 256);
	_stprintf_s(m_csBuffer, 
		_T("TIME:%02d:%02d:%02d %02d:%02d:%02d"),
		ms / 1000 / 60,
		ms / 1000 % 60,
		ms / 10 % 100,
		m_msLength / 1000 / 60,
		m_msLength / 1000 / 60,
		m_msLength / 10 % 100
		);
	return true;
}
bool	Sound::Render()
{
	std::wcout << m_csBuffer << std::endl;
	return true;
}
bool	Sound::Release()
{
	return true;
}
bool	Sound::Load(tstring szLoadName,FMOD::System* pSystem)
{
	assert(pSystem);
	// ../../../data/sound/xx.mp3
	TCHAR szDirve[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };
	_tsplitpath_s(szLoadName.c_str(), szDirve, szDir, szName, szExt);
	FileName = szName;
	FileName += szExt;
	m_pSystem = pSystem;

	// loading
	FMOD_RESULT hr;
	hr = pSystem->createSound(wtm(szLoadName).c_str(), FMOD_DEFAULT, 0, &m_pSound);
	if (hr != FMOD_OK) return false;

	m_pSound->getLength(&m_msLength, FMOD_TIMEUNIT_MS);	
	m_pChannel->setVolume(0.5f);
	return true;
}
void	Sound::PlayEffect()
{
	FMOD_RESULT hr;
	hr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
	if (hr != FMOD_OK) return;
}
void	Sound::Play()
{
	FMOD_RESULT hr;
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (!playing)
	{
		hr = m_pSystem->playSound(m_pSound, nullptr, false, &m_pChannel);
		if (hr != FMOD_OK) return;
	}
}
void	Sound::Paused()
{
	bool playing = false;
	if (m_pChannel != nullptr)
	{
		m_pChannel->isPlaying(&playing);
	}
	if (playing)
	{
		bool paused = false;
		m_pChannel->getPaused(&paused);
		m_pChannel->setPaused(!paused);
	}
}
void	Sound::Stop() 
{
	m_pChannel->stop();
}
void	Sound::VolumeUp() 
{
	float fVolume = 1.0f;
	m_pChannel->getVolume(&fVolume);
	m_fVolume = min(1.0f, fVolume + 0.1f * World::FramePerSecond);
	m_pChannel->setVolume(m_fVolume);
}
void	Sound::VolumeDown() 
{
	float fVolume = 1.0f;
	m_pChannel->getVolume(&fVolume);
	m_fVolume = max(0.0f, fVolume - 0.1f * World::FramePerSecond);
	m_pChannel->setVolume(m_fVolume);
}
void	Sound::SetMode(DWORD dwMode) 
{
	m_pSound->setMode(dwMode);
}
Sound::Sound(tstring FileName) :
	FileName{ std::move(FileName)},
	m_pSystem {nullptr},
	m_pSound{ nullptr },
	m_fVolume {0.5f}
{
	
}
Sound::~Sound() 
{}