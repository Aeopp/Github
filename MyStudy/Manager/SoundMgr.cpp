#include "SoundMgr.h"
#include <utility>
#include "Util.h"
bool SoundMgr::Load(Key_Type LoadName) noexcept
{
	// 사운드를 동적 할당 이후 초기화 작업 수행
	// 초기화가 실패시 아무것도 안하거나 예외 전파로 클라이언트에게 알린다.
	if (Sound_ptr load_sound = std::make_unique<Sound>();
		load_sound->Init())
	{
		// 해당 Key 로 로딩이 성공 하였다면 
		// Map 에 삽입하고 성공하였다고 알린다.
		if (load_sound->Load(LoadName)) {
			auto [dummy, isInsert] = Map.insert(make_pair(LoadName,std::move(load_sound) ));
			// 로딩까지 성공하였으나 이미 맵에 존재한다면 삽입은 실패한다.
			return isInsert;
		}
	}
	
	return false;

	/*	throw std::exception(Log("load_sound->Init() Fail"));*/
	// Sound 할당 이후 초기화
}

bool SoundMgr::clear() noexcept
{
	return true; 
}

typename SoundMgr::Sound_ptr SoundMgr::getSoundPtr(const Key_Type& Param_key)
{
	// Map 에서 해당키에 맞는 사운드 검색
	// 레퍼런스를 반환하거나 존재하지 않는다면
	// 클라에게 알려준다

	if (auto Iter = Map.find(Param_key);
		Iter != std::end(Map))
	{
		return std::move(Iter->second);
	}
	else
		return std::make_unique<Sound>();

}
