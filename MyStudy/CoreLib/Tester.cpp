#pragma once
#include "Tester.h"
#include "Core.h"
#include <windows.h>
using namespace std::literals::chrono_literals;

bool Tester::Frame()
{
	_Hero.Frame();

	for (auto& Npc : _Npcs)
		Npc.Frame();

	return true;
};

bool Tester::Render()
{
	_BackGround.Render(_HOffScreenDC);
	_Hero._Mesh.Render(_HOffScreenDC);

	for (auto& Npc : _Npcs)
		Npc._Mesh.Render(_HOffScreenDC);
	
	auto& _WorldRect = world::RectClient;
	
	BitBlt(_HScreenDC, 0, 0, world::RectClient.right, world::RectClient.bottom,
	_HOffScreenDC,0,0,SRCCOPY	);

	return true; 
};

bool Tester::Init()noexcept
{
	// TODO ::  Test Code
	const std::wstring _key1 = L"../../../Data/Sound/romance.mid";
	const std::wstring _key2 = L"../../../Data/Sound/MyLove.mp3";
	const std::wstring _key3 = L"../../../Data/Sound/GunShot.mp3";

	using _Key = Input::EKey;

	auto& _Sound_Ref = Super::_Sound_Mgr;
	auto& _Input_Ref = Super::_Input_Helper;

	_Sound_Ref.Load(_key1);
	_Sound_Ref.Load(_key2);
	_Sound_Ref.Load(_key3);

	_Input_Ref.Func_Regist({ '1' }, { _Key::Press,_Key::Press }  ,&SoundMgr::play_sound,
		std::ref(_Sound_Ref), _key1);

	_Input_Ref.Func_Regist({ '2'
		}, { _Key::Press , _Key::Press }, &SoundMgr::play_sound,
		std::ref(_Sound_Ref), _key2);

	_Input_Ref.Func_Regist({ '3' }, {_Key::Press, _Key::Press
}, & SoundMgr::play_effect,
		std::ref(_Sound_Ref), _key3);

	_Input_Ref.Func_Regist({'P'
		}, { _Key::Press,_Key::Press } ,  &SoundMgr::pause,
		std::ref(_Sound_Ref), _key1);
	//VK_HOME
	_Input_Ref.Func_Regist({ 0x24 }, { _Key::Hold,_Key::Hold }, &SoundMgr::Volume_Up,
		std::ref(_Sound_Ref), _key1);
	//VK_END
	_Input_Ref.Func_Regist({0x23
}, { _Key::Hold,_Key::Hold }, & SoundMgr::Volume_Down,
	std::ref(_Sound_Ref), _key1);

	//TODO :: ESC Push -> Core Run 에 Notify 해서 루프를 바로 종료할수 있다면 적용할 것
	//TODO :: 적용하고 Core::Run 키 체킹 코드 지울것
	auto Exit = [this] {IsExit = true; };
	
	_Input_Ref.Func_Regist({ 0x18 }, { _Key::Press,_Key::Press }, Exit);
	// TODO :: Delete plz...

	// shared_ptr 이 소멸할때 ReleaseDC 를 호출해 핸들 안전하게 해제 
	auto ScreenDC_Deleter = _HWnd;
	
	/*_HScreenDC = HDC(GetDC(_HWnd),
		ScreenDC_Deleter);
	
	_HOffScreenDC = HDC(
		CreateCompatibleDC(_HScreenDC), ScreenDC_Deleter);
	
	_HOffScreenBitmap = HBITMAP
	(CreateCompatibleBitmap(_HScreenDC,
	world::RectClient.right, world::RectClient.bottom),
		util::Bitmap_Deleter());*/

	SelectObject(_HOffScreenDC, _HOffScreenBitmap);
	
	_BackGround.Load(_HScreenDC, L"../../../Data/kgcabk.bmp");
	
	if (_Hero._Mesh.Load(_HScreenDC, L"../../../Data/bitmap1.bmp"))
	{
		RECT _RectSrc, _RectDest;

		_RectSrc.left = 133;
		_RectSrc.top = 1;

		auto& [_DestLeft, _DestTop, _DestRight, _DestBottom] = _RectDest;

		_DestLeft = world::RectClient.right / 2;
		_DestTop = world::RectClient.bottom / 2;
		_DestRight = 42;
		_DestBottom = 60;

		_Hero._Mesh.SetRect(_RectSrc, _RectDest);
	}

	// 로딩이 성공적인 객체는 Rect 를 세팅해주고 그렇지 않은 객체는 지웁니다.
	
	auto Pred = [this](ANpc& Npc)
	{
		return Npc._Mesh.Load(_HScreenDC, L"../../../data/bitmap1.bmp");
	};
	
	auto transform = [](ANpc& Npc)
	{
		RECT Rect_Src, Rect_Dest;
		
		Rect_Src.left = 46;
		Rect_Src.top = 63;
		
		Rect_Dest.left = world::Random.Get(0, 800, 1).back();
		Rect_Dest.top = world::Random.Get(0, 600, 1).back();
		Rect_Dest.right = 68;
		Rect_Dest.bottom = 78;
		
		Npc._Mesh.SetRect(Rect_Src, Rect_Dest);
	};
	
	/*auto new_end = std::transform_if(std::begin(_Npcs), std::end(_Npcs), std::begin(_Npcs),Pred, transform);
	*/
//	_Npcs.erase(new_end, std::end(_Npcs));
	
	return true; 
}

bool Tester::Clear() noexcept
{
	/*_BackGround.Clear();
	_Hero.Clear();*/

	/*for(auto& Npc : _Npcs)
	{
		
	}
	*/
	/*DeleteObject(_HOffScreenBitmap);
	ReleaseDC(_hwnd)*/

		return true; 
};

