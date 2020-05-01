#include "Core.h"
using namespace std::literals::chrono_literals;
bool Core::Core_Init() noexcept
{
	return true; 
}

bool Core::Core_Clear() noexcept
{
	return true; 
}

bool Core::Core_Frame()
{
	return true;
}

bool Core::Core_Render()
{
	this->Render();

	_Timer.Render();
	util::GetInstance<SoundMgr>().Render();
	util::GetInstance<Input>().Render();

	return true;
}

Core::Core()
{
	isExit = false; 
}

bool Core::Frame()
{
	_Timer.Frame();
	util::GetInstance<SoundMgr>().Frame();
	util::GetInstance<Input>().Frame(); 

	this->Frame();

	return true; 
}

bool Core::Render()
{
	return false;
}

bool Core::Init() noexcept
{
	_Timer.Init();
	util::GetInstance<SoundMgr>().Init();
	util::GetInstance<Input>().Init();

	this->Init();
	return true; 
}

bool Core::Clear() noexcept
{
	return false;
}

bool Core::Run()&
{
	auto Delay = 15ms; 

	Core_Init();

	while (!isExit) {
		Core_Frame();
		Core_Render();

		std::this_thread::sleep_for(Delay);
	};
	Core_Clear();
	return true; 
}
