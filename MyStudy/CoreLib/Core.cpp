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
	_Timer.Clear();
	_Sound_Mgr.Clear();
	_Input_Helper.Clear();
	Clear();
	return true;
};

bool Core::Core_Frame()
{
	_Timer.Frame();
	_Sound_Mgr.Frame();
	_Input_Helper.Frame();
	// Input 에서 VK_ESCAPE 를 검사
	if (isExit == true) return false;
	Frame(); 
	return true;
};

bool Core::Core_Render()
{
	_Timer.Render();
	_Sound_Mgr.Render();
	_Input_Helper.Render();
	
	Render();
	return true;
}

Core::Core() : _Input_Helper{util::GetInstance<Input>()} ,
				_Sound_Mgr{util::GetInstance<SoundMgr>()},
				Delay{50ms},
				isExit{false } 
				{}

Core::~Core() noexcept
{
	Core_Clear(); 
}


bool Core::Run()&
{
	Core_Init();

	while (isExit==false) {
		
		if (Core_Frame() == false && isExit == true)
			break;
		
		Core_Render();
		std::this_thread::sleep_for(Delay);
	};

	// TODO :: RAII 
	//Core_Clear();
	
	return true; 
}
