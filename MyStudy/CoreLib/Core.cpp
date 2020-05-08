#pragma once
#include "Core.h"

using namespace std::literals::chrono_literals;

bool Core::Frame_Implementation()
{
	_Timer.Frame();
	_Sound_Mgr.Frame();
	_Input_Helper.Frame();
	// Input 에서 VK_ESCAPE 를 검사
	if (MyWindow::IsExit == true) return false;

	Frame();
	
	return true;
};

bool Core::Render_Implementation()
{
	PreRender();
	Render(); 

	_Timer.Render();
	_Sound_Mgr.Render();
	_Input_Helper.Render();
	
	PostRender();
	
	return true; 
}

bool Core::Init_Implementation()noexcept
{
	Delay = 50ms;
	MyWindow::IsExit = false;
	// Window 생성시점에 이미 초기화 되있는 핸들 
	_HScreenDC = GetDC(_HWnd);

	_HOffScreenDC = CreateCompatibleDC(_HScreenDC);
	
	_HOffScreenBitmap = CreateCompatibleBitmap(_HScreenDC,
		world::RectClient.right,
		world::RectClient.bottom);

	auto _ColorRef = RGB(255, 0, 0); 
	_HBrushBackGround =  CreateSolidBrush(_ColorRef);

	_HDefaultFont = CreateFont(20, 0, 0, FW_BOLD, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, 0, L"궁서");

	_HFont = CreateFont(30, 0, 0, FW_BOLD, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"고딕");

	SelectObject(_HOffScreenDC, _HBrushBackGround);
	SelectObject(_HOffScreenDC, _HDefaultFont);
	SelectObject(_HOffScreenDC, _HOffScreenBitmap);
	
	return true;
}



Core::Core() : _Input_Helper{ util::GetInstance<Input>() },
_Sound_Mgr{ util::GetInstance<SoundMgr>() },
_BitmapManager{ util::GetInstance<BitmapManager>() }
{
	Init_Implementation();
};

Core::~Core() noexcept
{
	Clear_Implementation();
};

bool Core::Clear_Implementation() noexcept
{
	DeleteObject(_HDefaultFont);
	DeleteObject(_HFont);
	DeleteObject(_HBrushBackGround);
	DeleteObject(_HOffScreenBitmap);
	ReleaseDC(_HWnd, _HOffScreenDC);
	ReleaseDC(_HWnd, _HScreenDC); 

	return true; 
}

bool Core::PreRender()
{
	int a = 12;
	
	PatBlt(_HOffScreenDC,
		0, 0, world::RectClient.right,
		world::RectClient.bottom,
		PATCOPY);
	
	return true; 
}

bool Core::PostRender()
{
	BitBlt(_HScreenDC, 0, 0, world::RectClient.right, world::RectClient.bottom,
		_HOffScreenDC, 0, 0, SRCCOPY);
	
	return true; 
};

bool Core::Run()&
{
	while (MyWindow::IsExit==false) {

		if(WinRun())
		{
			Frame_Implementation();
			Render_Implementation();
			std::this_thread::sleep_for(Delay);
		}
	};
	
	return true; 
}
