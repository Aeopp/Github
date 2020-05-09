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
		// ���带 ���� �Ҵ� ���� �ʱ�ȭ �۾� ����
		// �ʱ�ȭ�� ���н� (�Ķ���Ͱ� �߸��Ǿ������) �ƹ��͵� ���Ѵ�	
	}

	// ../../../data/sound/filename.mp3 -> filename.mp3
	// ���ڿ��� �ùٸ� ��������� �˻����� �ʴ´�.
	auto filename = File::PathDelete(FullPath);

	std::weak_ptr<Sound> ReturnValue;

	if (auto find_iter = Map.lower_bound(filename);
		find_iter == std::end(Map) || find_iter->first > filename)
	{
		if (auto _Sound = std::make_shared<Sound>();
			_Sound->Init())
		{
			//				TODO:: �ε��� FullPath
			if (_Sound->Load(F_System, FullPath, filename)) {
				// TODO :: ������ü�� �̸��� �����ϴ� ���� �߰�
				auto iter = Map.try_emplace(
					std::move(find_iter), std::move(filename), std::move(_Sound));
				// ������ �������϶��� �������� �� ��ȿ�� ���� �������ش�.
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
	// �ڵ� ��ȯ
	F_System->close();
	F_System->release();
	return true; 
};

bool SoundMgr::Init() noexcept
{
	FMOD_RESULT F_Result;
	
	F_Result = FMOD::System_Create(&F_System);

	{
		// FMOD �ý��� �ε� ����
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

	// update �Լ��� �������Ӹ��� �ݵ�� ȣ����������� �䱸��
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
		
		// Current_Bgm �� ����Ǿ������� ����������� ������ ���� ���
		// Current_Bgm �� �����ϰ� ����
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

