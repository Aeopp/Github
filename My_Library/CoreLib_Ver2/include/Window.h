#pragma once
#include <memory>
#include <windows.h>
class Window
{
public:
	std::shared_ptr<HINSTANCE__> InstanceHandle;
	std::shared_ptr<HWND__> WindowHandle;
	bool		Exit;
	RECT		ClientRect;
	RECT		WindowRect;
private:
	MSG			_Message;
public:
	bool SetWindow(HINSTANCE hInstance);
	bool WindowRun();
	virtual bool GameRun();
public :
	Window();
	Window(const Window&)=default;
	Window& operator=(const Window&)=default;
	virtual ~Window()noexcept;
	Window(Window&&)noexcept=default;
	Window& operator=(Window&&)noexcept=default;
	
};

