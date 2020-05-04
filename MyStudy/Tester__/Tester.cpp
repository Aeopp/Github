#include "Tester.h"
#include "Core.h"
#include <windows.h>
using namespace std::literals::chrono_literals;

bool Tester::Frame()
{
	return true; 
}

bool Tester::Render()
{
	return true; 
};

bool Tester::Init() 
{
	// TODO ::  Test Code
	const std::wstring _key1 = L"../../Data/Sound/romance.mid";
	const std::wstring _key2 = L"../../Data/Sound/MyLove.mp3";
	const std::wstring _key3 = L"../../Data/Sound/GunShot.mp3";

	using _Key = Input::EKey;
	
	auto& _Sound_Ref = Super::_Sound_Mgr;
	auto& _Input_Ref  = Super::_Input_Helper;
	
	_Sound_Ref.Load(_key1);
	_Sound_Ref.Load(_key2);
	_Sound_Ref.Load(_key3);

	_Input_Ref.Func_Regist('1', _Key::Press,&SoundMgr::play_sound,
	std::ref(_Sound_Ref),_key1);
	
	_Input_Ref.Func_Regist('2', _Key::Press,&SoundMgr::play_sound, 
	std::ref(_Sound_Ref),_key2);

	_Input_Ref.Func_Regist('3', _Key::Press,&SoundMgr::play_effect,
	std::ref(_Sound_Ref),_key3);

	_Input_Ref.Func_Regist('P', _Key::Press,&SoundMgr::pause,
	std::ref(_Sound_Ref), _key1);
							//VK_HOME
	_Input_Ref.Func_Regist(0x24, _Key::Hold, &SoundMgr::Volume_Up,
	std::ref(_Sound_Ref),_key1);
							//VK_END
	_Input_Ref.Func_Regist(0x23, _Key::Hold, &SoundMgr::Volume_Down,
	std::ref(_Sound_Ref), _key1);

	//TODO :: ESC Push -> Core Run �� Notify �ؼ� ������ �ٷ� �����Ҽ� �ִٸ� ������ ��
	//TODO :: �����ϰ� Core::Run Ű üŷ �ڵ� �����
	auto Exit = [this] {IsExit = true; };
	
	_Input_Ref.Func_Regist(0x18, _Key::Press, Exit); 
	// TODO :: Delete plz...
	return true; 
}

bool Tester::Clear() noexcept
{
	return true;
};

