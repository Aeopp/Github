#include "Core.h"
#include "Mesh.h"
class _Tester : public Core
{
public:
	virtual bool Init()noexcept override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Clear()noexcept  override;
private:
	HDC_ptr _HScreenDC;
	HDC_ptr _HOffScreenDC;
	HBITMAP_ptr _HOffScreenBitmap;
	
	Mesh _BackGround;
};
bool _Tester::Init()
{
	// TODO ::  Test Code
	//const std::wstring Dummy = L"‪../../Data/Sound/romanse.mid";

	const std::wstring _key1 = L"../../Data/Sound/MyLove.mp3";
	const std::wstring _key2 = L"../../Data/Sound/OnlyLove.mp3";
	const std::wstring _key3 = L"../../Data/Sound/GunShot.mp3";


	using _Key = Input::EKey;

	auto& _Sound_Ref = Super::_Sound_Mgr;
	auto& _Input_Ref = Super::_Input_Helper;

	//_Sound_Ref.Load(Dummy);

	_Sound_Ref.Load(_key1);
	_Sound_Ref.Load(_key2);
	_Sound_Ref.Load(_key3);

	_Input_Ref.Func_Regist({ '1' }, { _Key::Press ,_Key::Press }, &SoundMgr::play_sound,
		std::ref(_Sound_Ref), _key1);

	_Input_Ref.Func_Regist({ '2'
		}, { _Key::Press ,_Key::Press }, &SoundMgr::play_sound,
		std::ref(_Sound_Ref), _key2);

	_Input_Ref.Func_Regist({ '3' }, { _Key::Press ,_Key::Press }, &SoundMgr::play_effect,
		std::ref(_Sound_Ref), _key3);

	_Input_Ref.Func_Regist({ 'P'
		}, { _Key::Press ,_Key::Press }, &SoundMgr::pause,
		std::ref(_Sound_Ref), _key1);
	//VK_HOME
	_Input_Ref.Func_Regist({ 0x24 }, { _Key::Hold ,_Key::Hold }, &SoundMgr::Volume_Up,
		std::ref(_Sound_Ref), _key1);
	//VK_END
	_Input_Ref.Func_Regist({0x23
}, { _Key::Hold ,_Key::Hold }, & SoundMgr::Volume_Down,
		std::ref(_Sound_Ref), _key1);
	
	//TODO :: ESC Push -> Core Run 에 Notify 해서 루프를 바로 종료할수 있다면 적용할 것
	//TODO :: 적용하고 Core::Run 키 체킹 코드 지울것
	auto Exit = [this] {IsExit = true; };

	_Input_Ref.Func_Regist({ 0x18 }, { _Key::Press,_Key::Press }, Exit);
	// TODO :: Delete plz...
	return true;
}

//
//int WINAPI wWinMain
//(HINSTANCE hInstance,
//	HINSTANCE hPrevInstance,
//	LPWSTR lpCmdLine,
//	int nCmdShow)
//{
//	_Tester win;
//
//	if (win.SetWindow(hInstance))
//	{
//		win.Run();
//	}
//}
