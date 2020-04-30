#include "SoundMgr.h"
#include <utility>
#include "Util.h"
#include <algorithm>
#include <functional>
bool SoundMgr::Load(Key_Type LoadName) noexcept(false)
{
	if (F_System == nullptr )
		throw std::exception(Log("Sound Manager FMOD_System NotReady")); 
	// ���带 ���� �Ҵ� ���� �ʱ�ȭ �۾� ����
	// �ʱ�ȭ�� ���н� (�Ķ���Ͱ� �߸��Ǿ������) �ƹ��͵� ���Ѵ�
	
	// ����Ʈ �����Ϳ� Ŀ���� ������

	if (auto load_sound = std::make_shared<Sound>();
		load_sound->Init()) {

		if (load_sound->Load(LoadName, F_System)) {
			auto [Iter, IsInsert] =
				Map.try_emplace(std::move(LoadName), load_sound);
			// ���� �������� ����
			return IsInsert;
		}
	}
	return false;
}

bool SoundMgr::clear() noexcept
{
	Map.clear();
	// FMOD ���̺귯�� �Լ�ȣ��
	F_System->close();
	F_System->release();
	return true; 
};

bool SoundMgr::Init() noexcept(false)
{
	FMOD_RESULT F_Result; 
	F_Result = FMOD::System_Create(&F_System); 
	// FMOD �ý��� �ε� ����
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

	// update �Լ��� �������Ӹ��� �ݵ�� ȣ����������� �䱸��
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
	// Map ���� �ش�Ű�� �´� ���� �˻�
	// ����ڴ� ����ũ�����Ͱ� ��ȿ���� �˻��ϰ� ����ؾ��Ѵ�.
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
