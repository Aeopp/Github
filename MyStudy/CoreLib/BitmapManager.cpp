#include "BitmapManager.h"
#include <utility>
#include "Util.h"
#include <algorithm>
#include <functional>
#include "Convenience_function.h"

bool SoundMgr::Load(Key_Type LoadName) noexcept(false)
{
	if (F_System == nullptr)
		throw std::exception(Debug::Log("Sound Manager FMOD_System NotReady").c_str());
	// ���带 ���� �Ҵ� ���� �ʱ�ȭ �۾� ����
	// �ʱ�ȭ�� ���н� (�Ķ���Ͱ� �߸��Ǿ������) �ƹ��͵� ���Ѵ�

	// ����Ʈ �����Ϳ� Ŀ���� ������
	// ../../../data/sound/xxx.mp3
	// ��ū�� �и��Ѵ�. �̸��� �����ϴ°��� ȿ����
	TCHAR szDrive[MAX_PATH] = { 0, };
	TCHAR szDir[MAX_PATH] = { 0, };
	TCHAR szName[MAX_PATH] = { 0, };
	TCHAR szExt[MAX_PATH] = { 0, };

	_wsplitpath_s(P_ReadType.c_str(),
		szDrive, szDir, szName, szExt);

	TCHAR szFileName = szName;
	csFileName += szExt;

	// �̹� �ε��Ǿ��ִ� ������ ������ �ε������ʰ� ��ȯ
	for (auto& [first, second] : Map) {
		if (second.Name == LoadName) {
			return first;
		}
	}


	if (auto load_sound = std::make_shared<Sound>();
		load_sound->Init()) {

		if (load_sound->Load(LoadName, F_System)) {
			// TODO :: ������ü�� �̸��� �����ϴ� ���� �߰�
			auto [Iter, IsInsert] =
				Map.try_emplace(std::move(LoadName), load_sound);
			// ���� �������� ����
			return IsInsert;
		}
	}
	return false;
}

bool SoundMgr::Clear() noexcept
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
		throw std::exception(Debug::Log("FMOD SYSTEM Create Fail").c_str());
	//return false;
	F_Result = F_System->init(32, FMOD_INIT_NORMAL, 0);
	if (F_Result != FMOD_OK)
		throw std::exception(Debug::Log("FMOD SYSTEM Initaliaze Fail").c_str());
	//return false;

// TODO ::Load �� ù��° ���带 ����� �ε����� ���ϴ� ���׶�����
// TODO :: ���̵����ͷ� �ε���Ŵ
//this->Load(Key_Type{});

	return true;
}

bool SoundMgr::Frame()
{
	if (F_System == nullptr) return false;
	// throw std::exception(Log("FMOD System Not Ready"));
	for (auto& [_key, Sound] : Map)
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
	return this->get_sound_ptr(Param_key);
};
void SoundMgr::play_sound(const Key_Type& Param_key)& {

	auto _sound_weak = getSound(Param_key);

	if (auto _sound = _sound_weak.lock()) {
		_sound->Play();

		// Current_Bgm �� ����Ǿ������� ����������� ������ ���� ���
		// Current_Bgm �� �����ϰ� ����
		if (Current_Bgm.expired()) {
			Current_Bgm = _sound_weak;
			return;
		}
		else if (auto Current = Current_Bgm.lock();
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

void SoundMgr::play_effect(const Key_Type& Param_key)&
{
	auto _sound = get_sound_ptr(Param_key);
	_sound->PlayEffect();
}

bool SoundMgr::pause(const Key_Type& Param_key)&
{
	if (auto sound_ptr = get_sound_ptr(Param_key))
	{
		sound_ptr->Pause();
		return true;
	}
	else  return false;
}

bool SoundMgr::stop(const Key_Type& Param_key)&
{
	if (auto _sound = get_sound_ptr(Param_key))
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

bool SoundMgr::Volume_Up(const Key_Type& Param_key)&
{
	if (auto _sound = get_sound_ptr(Param_key))
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
