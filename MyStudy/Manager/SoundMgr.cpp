#include "SoundMgr.h"
#include <utility>
#include "Util.h"
bool SoundMgr::Load(Key_Type LoadName) noexcept
{
	// ���带 ���� �Ҵ� ���� �ʱ�ȭ �۾� ����
	// �ʱ�ȭ�� ���н� �ƹ��͵� ���ϰų� ���� ���ķ� Ŭ���̾�Ʈ���� �˸���.
	if (Sound_ptr load_sound = std::make_unique<Sound>();
		load_sound->Init())
	{
		// �ش� Key �� �ε��� ���� �Ͽ��ٸ� 
		// Map �� �����ϰ� �����Ͽ��ٰ� �˸���.
		if (load_sound->Load(LoadName)) {
			auto [dummy, isInsert] = Map.insert(make_pair(LoadName,std::move(load_sound) ));
			// �ε����� �����Ͽ����� �̹� �ʿ� �����Ѵٸ� ������ �����Ѵ�.
			return isInsert;
		}
	}
	
	return false;

	/*	throw std::exception(Log("load_sound->Init() Fail"));*/
	// Sound �Ҵ� ���� �ʱ�ȭ
}

bool SoundMgr::clear() noexcept
{
	return true; 
}

typename SoundMgr::Sound_ptr SoundMgr::getSoundPtr(const Key_Type& Param_key)
{
	// Map ���� �ش�Ű�� �´� ���� �˻�
	// ���۷����� ��ȯ�ϰų� �������� �ʴ´ٸ�
	// Ŭ�󿡰� �˷��ش�

	if (auto Iter = Map.find(Param_key);
		Iter != std::end(Map))
	{
		return std::move(Iter->second);
	}
	else
		return std::make_unique<Sound>();

}
