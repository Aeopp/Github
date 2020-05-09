#pragma once
#include <windows.h>
class Window
{
public:
	HINSTANCE	InstanceHandle;
	HWND		WindowHandle;
	bool		bExit;
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
	virtual ~Window()noexcept;
	Window(Window&&)                  noexcept      =default ;
	Window(const Window&)             noexcept      =default ;
	Window& operator=(Window&&)        noexcept     =default ;
	Window& operator=(const Window&)  noexcept      =default ;
};

