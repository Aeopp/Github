#pragma once
#include "Object.h"
#include <fmod.h>
#include <fmod.hpp>
#include <fmod_errors.h>

class Sound : public Object
{
private:	
	struct  DeleterDummy {
		template<typename HandleType>
		void operator()(HandleType) {
			static_assert(std::is_pointer_v<HandleType>, L"포인터가 아니잖아!!!");
		};
	};

	std::weak_ptr<FMOD::System>		FmodSystem;
	std::unique_ptr<FMOD::Sound,struct DeleterDummy>	FmodSound;
	std::unique_ptr<FMOD::Channel,struct DeleterDummy>	FmodChannel;
public:
	tstring			FileName;
	tstring			TimePassed;
	float_t			Volume;
	uint32_t Length;
public:	
	bool	Frame()override;
	bool	Render()override;
public:
	void	Paused();
	void	Stop();
	void	VolumeUp();
	void	VolumeDown();
	void	SetMode(uint32_t Mode);
public:
	void	Play();
	void	PlayEffect();
public:
	Sound(tstring FullPath,std::shared_ptr<FMOD::System> pSystem);
	virtual ~Sound();
	Sound(Sound&&)noexcept = default;
	Sound& operator=(Sound&&)noexcept = default;
	Sound(const Sound&) = default;
	Sound& operator=(const Sound&) = default;

};

