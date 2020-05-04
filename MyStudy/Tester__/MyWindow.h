#pragma once
#include <windows.h>
class MyWindow
{
public:
	bool SetWindow(HINSTANCE hinstance)& ;
	bool WinRun()&;
	virtual bool GameRun()&;
	
	MyWindow();
	virtual ~MyWindow() noexcept= default;
protected:
	bool IsExit;
private:
	HINSTANCE hInstance;
	HWND hWnd;
	MSG msg;
};

