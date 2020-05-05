#include "SoundMgr.h"
#include <utility>
#include "Util.h"
#include <algorithm>
#include <functional>
bool SoundMgr::Load(Key_Type LoadName) noexcept(false)
{
	if (F_System == nullptr )
		throw std::exception(Debug::Log("Sound Manager FMOD_System NotReady").c_str()); 
	// 사운드를 동적 할당 이후 초기화 작업 수행
	// 초기화가 실패시 (파라미터가 잘못되었을경우) 아무것도 안한다
	
	// 스마트 포인터용 커스텀 딜리터

	if (auto load_sound = std::make_shared<Sound>();
		load_sound->Init()) {

		if (load_sound->Load(LoadName, F_System)) {
			auto [Iter, IsInsert] =
				Map.try_emplace(std::move(LoadName), load_sound);
			// 삽입 성공여부 리턴
			return IsInsert;
		}
	}
	return false;
}

bool SoundMgr::Clear() noexcept
{
	Map.clear();
	// FMOD 라이브러리 함수호출
	F_System->close();
	F_System->release();
	return true; 
};

bool SoundMgr::Init() noexcept(false)
{
	FMOD_RESULT F_Result; 
	F_Result = FMOD::System_Create(&F_System); 
	// FMOD 시스템 로딩 실패
	if (F_Result != FMOD_OK)
		throw std::exception(Debug::Log("FMOD SYSTEM Create Fail").c_str());
		//return false;
	F_Result = F_System->init(32, FMOD_INIT_NORMAL, 0);
	if (F_Result != FMOD_OK) 
		throw std::exception(Debug::Log("FMOD SYSTEM Initaliaze Fail").c_str());
		//return false;

	// TODO ::Load 시 첫번째 사운드를 제대로 로드하지 못하는 버그때문에
	// TODO :: 더미데이터로 로딩시킴
	//this->Load(Key_Type{});

	return true; 
}

bool SoundMgr::Frame()
{
	if (F_System == nullptr) return false;  
	// throw std::exception(Log("FMOD System Not Ready"));
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
	return this->get_sound_ptr(Param_key);
};
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

void SoundMgr::play_effect(const Key_Type& Param_key) &
{
	auto _sound = get_sound_ptr(Param_key);
	_sound->PlayEffect(); 
}

bool SoundMgr::pause(const Key_Type& Param_key) &
{
	if (auto sound_ptr = get_sound_ptr(Param_key))
	{
		sound_ptr->Pause();
		return true;
	}
	else  return false; 
}

bool SoundMgr::stop(const Key_Type& Param_key) &
{
	if ( auto _sound = get_sound_ptr(Param_key))
	{
		if (_sound->isPlay())
		{
			_sound->Stop();
			return true;
		}
		else
			return false; 
	}
}

bool SoundMgr::Volume_Up(const Key_Type& Param_key) &
{
	if ( auto _sound = get_sound_ptr(Param_key) ) 
	{
		_sound->Volume_Up();
		return true; 
	}
	else
		return false; 
}

bool SoundMgr::Volume_Down(const Key_Type& Param_key)&
{
	if (auto _sound = get_sound_ptr(Param_key))
	{
		_sound->Volume_Up();
		return true;
	}
	else
		return false;
}

typename SoundMgr::Sound_ptr SoundMgr::get_sound_ptr(const Key_Type& Param_key)&
{
	if (auto Iter = Map.find(Param_key);
		Iter != std::end(Map))
		return Iter->second;
	else
		return typename SoundMgr::Sound_ptr{};
}

SoundMgr::SoundMgr() :F_System{ nullptr }
{
}

SoundMgr::~SoundMgr() noexcept
{
	Clear(); 
}
