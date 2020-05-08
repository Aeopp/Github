#pragma once
#include <windows.h>
#include "Util.h"
class MyWindow
{
public:
	MyWindow();
	bool WinRun()&;
	bool SetWindow(HINSTANCE hinstance)&;
	virtual bool GameRun()&;
	virtual ~MyWindow() noexcept= default;
protected:
	bool IsExit;
	//  World 와 소유권 공유중인 포인터
	HINSTANCE _HInstance;
	HWND _HWnd;
private:
	RECT _RectClient;
	RECT _RectWindow;
	MSG msg;
};

