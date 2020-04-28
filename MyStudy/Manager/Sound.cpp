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
		// Param �� ��������� Ȯ���ڰ� ��ȿ���� ������
		// Param ���� �� Sound �� �ε��Ҽ� ���� ��
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
