#pragma once
#include <memory>
#include <windows.h>
class window
{
public:
	std::shared_ptr<HINSTANCE__> hInstance;
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
	window();
	window(const window&)=default;
	window& operator=(const window&)=default;
	virtual ~window()noexcept;
	window(window&&)noexcept=default;
	window& operator=(window&&)noexcept=default;
	
};

