#include "SoundMgr.h"
#include <utility>
#include "Util.h"
#include <algorithm>
#include <functional>
bool SoundMgr::Load(Key_Type LoadName) noexcept(false)
{
	if (F_System == nullptr )
		throw std::exception(Log("Sound Manager FMOD_System NotReady")); 
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

bool SoundMgr::clear() noexcept
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
		throw std::exception(Log("FMOD SYSTEM Create Fail"));
		//return false;
	F_Result = F_System->init(32, FMOD_INIT_NORMAL, 0);
	if (F_Result != FMOD_OK) 
		throw std::exception(Log("FMOD SYSTEM Initaliaze Fail"));
		//return false; 

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
}

typename SoundMgr::Sound_ptr SoundMgr::getSound(const Key_Type& Param_key)
{
	// Map 에서 해당키에 맞는 사운드 검색
	// 사용자는 유니크포인터가 유효한지 검사하고 사용해야한다.
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
	clear(); 
}
