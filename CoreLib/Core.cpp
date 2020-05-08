#include "Core.h"

using namespace std::literals::chrono_literals;

bool Core::Frame_Implementation()
{
	_Timer.Frame();
	_Sound_Mgr.Frame();
	_Input_Helper.Frame();
	// Input 에서 VK_ESCAPE 를 검사
	if (MyWindow::IsExit == true) return false;

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
	_HScreenDC = util::_GetDC(_HWnd);
	
	_HOffScreenDC = util::_CreateCompatibleDC(_HScreenDC, _HWnd);
	
	_HOffScreenBitmap = util::_CreateCompatibleBitmap(
		_HScreenDC,
		world::RectClient.right,
		world::RectClient.bottom);

	_HBrushBackGround = util::_CreateSolidBrush(RGB(255, 0, 0));

	_HDefaultFont = util::_CreateFont(20, 0, 0, FW_BOLD, 0, 0, 0, 0, 
		HANGEUL_CHARSET, 0, 0, 0, 0, L"궁서");

	_HFont = util::_CreateFont(30, 0, 0, FW_BOLD, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"고딕");
	

	SelectObject(_HOffScreenDC.get(), _HBrushBackGround.get());
	SelectObject(_HOffScreenDC.get(), _HDefaultFont.get());
	SelectObject(_HOffScreenDC.get(), _HOffScreenBitmap.get());
	
	return true;
}



Core::Core() : _Input_Helper{ util::GetInstance<Input>() },
			   _Sound_Mgr{ util::GetInstance<SoundMgr>() },
				_BitmapManager{util::GetInstance<BitmapManager>()}
{
	Init_Implementation();
}

Core::~Core() noexcept
{
	Clear_Implementation();
}


bool Core::Clear_Implementation() noexcept
{

}

bool Core::PreRender()
{
	PatBlt(_HOffScreenDC.get(),
		0, 0, world::RectClient.right,
		world::RectClient.bottom,
		PATCOPY);
	
	return true; 
}

bool Core::PostRender()
{
	BitBlt(_HScreenDC.get(), 0, 0, world::RectClient.right, world::RectClient.bottom,
		_HOffScreenDC.get(), 0, 0, SRCCOPY);
	
	return true; 
};

bool Core::Run()&
{
	while (MyWindow::IsExit==false) {

		if(WinRun())
		{
			Clear();
			Render();
			std::this_thread::sleep_for(Delay);
		}
	};
	
	return true; 
}
