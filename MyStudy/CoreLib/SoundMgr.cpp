#pragma once
#include "SoundMgr.h"
#include <utility>
#include "Util.h"
#include <algorithm>
#include <functional>

std::weak_ptr<Sound> SoundMgr::Load(const Key_Type& FullPath) noexcept(false)
{
	{
		if (F_System == nullptr)
			throw std::exception(Debug::Log("Sound Manager FMOD_System NotReady").c_str());
		// 사운드를 동적 할당 이후 초기화 작업 수행
		// 초기화가 실패시 (파라미터가 잘못되었을경우) 아무것도 안한다	
	}

	// ../../../data/sound/filename.mp3 -> filename.mp3
	// 문자열이 올바른 경로인지는 검사하지 않는다.
	auto filename = File::PathDelete(FullPath);

	std::weak_ptr<Sound> ReturnValue;

	if (auto find_iter = Map.lower_bound(filename);
		find_iter == std::end(Map) || find_iter->first > filename)
	{
		if (auto _Sound = std::make_shared<Sound>();
			_Sound->Init())
		{
			//				TODO:: 로딩은 FullPath
			if (_Sound->Load(F_System, FullPath, filename)) {
				// TODO :: 사운드자체에 이름을 저장하는 로직 추가
				auto iter = Map.try_emplace(
					std::move(find_iter), std::move(filename), std::move(_Sound));
				// 삽입이 성공적일때만 약포인터 에 유효한 값을 세팅해준다.
				if (std::end(Map) != iter)
					ReturnValue = iter->second;
			}
		};
	};
	return ReturnValue;
};

bool SoundMgr::Clear() noexcept
{
	Map.clear();
	// 핸들 반환
	F_System->close();
	F_System->release();
	return true; 
};

bool SoundMgr::Init() noexcept
{
	FMOD_RESULT F_Result;
	
	F_Result = FMOD::System_Create(&F_System);

	{
		// FMOD 시스템 로딩 실패
		if (F_Result != FMOD_OK)
		return false;
		F_Result = F_System->init(32, FMOD_INIT_NORMAL, 0);
		if (F_Result != FMOD_OK)
			return false; 
	}

	return true; 
}

bool SoundMgr::Frame()
{
	if (F_System == nullptr) return false;
	/*	throw std::exception(Debug::Log("FMOD System Not Ready").c_str());	*/
	
	for (auto&[_key,Sound] : Map) 
		Sound->Frame(); 

	// update 함수는 매프레임마다 반드시 호출해줘야함을 요구함
	F_System->update(); 
	return true; 
}

bool SoundMgr::Render()
{
	for (auto& [_key, Sound] : Map)
		Sound->Render();

	return true; 
};

std::weak_ptr<Sound> SoundMgr::getSound(const Key_Type& Param_key)
{
	return get_sound_ptr(Param_key);
};

void SoundMgr::play_effect(const Key_Type& Param_key)&
{
	if(auto _sound = get_sound_ptr(Param_key).lock();
		_sound)
	{
		_sound->PlayEffect();
	}
}

void SoundMgr::play_sound(const Key_Type& Param_key) &{
	
	auto _sound_weak = getSound(Param_key);
	
	if (auto _sound = _sound_weak.lock()) {
		_sound->Play();
		
		// Current_Bgm 이 만료되었을때는 현재재생중인 음악이 없을 경우
		// Current_Bgm 을 갱신하고 리턴
		if(Current_Bgm.expired())	{
			Current_Bgm = _sound_weak;
			return; 
		}
		else if(auto Current = Current_Bgm.lock();
			Current->getReadKey() == Param_key)
		{
			Current->Play();
			return;
		}
	}
	else return;
	
	if (auto Stop = Current_Bgm.lock();
		Stop->isPlay())
	{
		Current_Bgm.swap(_sound_weak); 
		Stop->Stop();
	};
}


bool SoundMgr::pause(const Key_Type& Param_key) &
{
	if (auto sound_ptr = get_sound_ptr(Param_key).lock() ; 
		sound_ptr)
	{
		sound_ptr->Pause();
		return true; 
	}
	return false; 
}

bool SoundMgr::stop(const Key_Type& Param_key) &
{
	if ( auto _sound = get_sound_ptr(Param_key).lock() ; 
		_sound)
	{
		if (_sound->isPlay())
		{
			_sound->Stop();
			return true;
		}
	}
}

bool SoundMgr::Volume_Up(const Key_Type& Param_key) &
{
	if ( auto _sound = get_sound_ptr(Param_key).lock();
		_sound)
	{
		_sound->Volume_Up();
		return true; 
	}
}

bool SoundMgr::Volume_Down(const Key_Type& Param_key)&
{
	if (auto _sound = get_sound_ptr(Param_key).lock();
		_sound)
	{
		_sound->Volume_Up();
		return true; 
	}
	return false; 
}

void SoundMgr::SetDefaultPath(const ReadType& SetPath)
{
	DefaultPath = SetPath; 
};

std::weak_ptr<Sound> SoundMgr::get_sound_ptr(const Key_Type& Param_key)&
{
	std::weak_ptr<Sound> ReturnValue;

	if (auto Iter = Map.find(Param_key);
		Iter != std::end(Map)) {
		ReturnValue = (Iter->second);
	};

	return ReturnValue;
};

