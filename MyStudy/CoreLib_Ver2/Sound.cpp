#include "Sound.h"
#include <sstream>
#include <algorithm>
bool	Sound::Frame()
{
	if (FmodChannel==nullptr) return true;
	uint32_t MiliSecond;
	FmodChannel->getPosition(&MiliSecond, FMOD_TIMEUNIT_MS);
	std::wstringstream WStringStream;
	WStringStream << L"TIME:" <<
		MiliSecond / 1000 / 60 <<
		MiliSecond / 1000 % 60 <<
		MiliSecond / 10 % 100 << L" " <<
		Length / 1000 / 60 <<
		Length / 1000 / 60 <<
		Length / 10 % 100;
	TimePassed = std::move(WStringStream.str());
	return true;
}
bool	Sound::Render()
{
	std::wcout << TimePassed << std::endl;
	return true;
}
void	Sound::PlayEffect()
{
	FMOD_RESULT FmodResult;
	if (auto SharedFmodSystem = FmodSystem.lock();
		SharedFmodSystem) {
		auto FModChannelHandle = FmodChannel.get();
		FmodResult = SharedFmodSystem->playSound(FmodSound.get(), nullptr, false,&FModChannelHandle);
	}
	if (FmodResult != FMOD_OK) return;
}
void	Sound::Play()
{
	FMOD_RESULT FmodResult;
	bool bPlay = false;
	if (FmodChannel != nullptr)
	{
		FmodChannel->isPlaying(&bPlay);
	}
	if (bPlay==false)
	{
		if (auto SharedFmodSystem = FmodSystem.lock();
			SharedFmodSystem) {
			auto FModChannelHandle = FmodChannel.get(); 
			FmodResult = SharedFmodSystem->playSound(FmodSound.get(), nullptr, false, &FModChannelHandle);
		}
		if (FmodResult != FMOD_OK) return;
	}
}
void	Sound::Paused()
{
	bool playing = false;
	if (FmodChannel != nullptr)
	{
		FmodChannel->isPlaying(&playing);
	}
	if (playing==true)
	{
		bool paused = false;
		FmodChannel->getPaused(&paused);
		FmodChannel->setPaused(!paused);
	}
}
void	Sound::Stop() 
{
	FmodChannel->stop();
}
void	Sound::VolumeUp() 
{
	FmodChannel->getVolume(&Volume);
	Volume =std::clamp<>(Volume +0.1f, 0.f, 1.f);
	FmodChannel->setVolume(Volume);
}
void	Sound::VolumeDown() 
{
	FmodChannel->getVolume(&Volume);
	Volume = std::clamp<>(Volume -0.1f, 0.f, 1.f);
	FmodChannel->setVolume(Volume);
}
void	Sound::SetMode(uint32_t Mode = FMOD_LOOP_NORMAL) 
{
	FmodSound->setMode(Mode);
}
Sound::Sound(tstring FullPath, std::shared_ptr<FMOD::System> pSystem) :
	Volume {0.5f},
	FmodChannel{ nullptr }
{
	assert(pSystem);
	// ../../../data/sound/xx.mp3
	FileName = Utility::PathDelete(FullPath);
	FmodSystem = pSystem;

	FMOD_RESULT FmodResult;
	FMOD::Sound* FModSoundHandle;

	FmodResult = pSystem->createSound(std::string(std::begin(FullPath), std::end(FullPath)).c_str(),FMOD_DEFAULT, 0, &FModSoundHandle);
	if (FmodResult != FMOD_OK) throw std::exception(Debug::Log("CreateSound Fail!!"));

	FmodSound = std::unique_ptr<FMOD::Sound,DeleterDummy>(FModSoundHandle,DeleterDummy{});
	FmodSound.reset(FModSoundHandle);
	FmodSound->getLength(&Length, FMOD_TIMEUNIT_MS);
}
Sound::~Sound() 
{}