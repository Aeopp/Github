#include "Sound.h"
#include <utility>
#include <exception>
#include <stdexcept>
#include "Util.h"

bool Sound::Init()noexcept
{
	return true;
}

bool Sound::Render()const
{
	return false;
}

bool Sound::Clear()noexcept
{
	return false;
}

bool Sound::Frame()
{
	return false;
}

bool Sound::Load(ReadType Param)
{
	if (Param.empty()) {
		// Param 이 비어있을시 확장자가 유효하지 않을시
		// Param 으로 된 Sound 를 로드할수 없을 시
		throw std::invalid_argument(__FUNCTION__"Param Empty");
		// return false; 
	}

	Name = std::move_if_noexcept(Param);
	return true;
}

bool Sound::Play() const
{
	// Play !! 
	if (Name.empty()) 
		return false;  
	
	return false; 
}
