#include "Core.h"

using namespace std::literals::chrono_literals;

bool Core::Core_Init() noexcept
{
	_Timer.Init();
	_Sound_Mgr.Init();
	_Input_Helper.Init();
	Init();
	return true; 
}

bool Core::Core_Clear() noexcept
{
	Clear();
	
	_Timer.Clear();
	_Sound_Mgr.Clear();
	_Input_Helper.Clear();
	
	return true;
};

bool Core::Core_Frame()
{
	_Timer.Frame();
	_Sound_Mgr.Frame();
	_Input_Helper.Frame();
	// Input 에서 VK_ESCAPE 를 검사
	if (/*MyWindow::*/IsExit == true) return false;
	Frame(); 
	return true;
};

bool Core::Core_Render()
{
	Render();
	
	_Timer.Render();
	_Sound_Mgr.Render();
	_Input_Helper.Render();
	return true;
}

Core::Core() : _Input_Helper{util::GetInstance<Input>()} ,
				_Sound_Mgr{util::GetInstance<SoundMgr>()},
				Delay{50ms}
				/*MyWindow::*/
{ /*MyWindow::*/IsExit = false; }

Core::~Core() noexcept
{
	Core_Clear(); 
}


bool Core::Run()&
{
	Core_Init();
	

	while (/*MyWindow::*/IsExit==false) {

		if(WinRun())
		{
			Core_Frame();
			Core_Render();
			std::this_thread::sleep_for(Delay);
		}
	};

	// TODO :: RAII 
	//Core_Clear();
	
	return true; 
}
