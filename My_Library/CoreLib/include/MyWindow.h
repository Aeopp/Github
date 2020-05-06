#pragma once
#include <windows.h>
#include "Util.h"
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
protected:
	//  World 와 소유권 공유중인 포인터
	HINSTANCE_ptr _HInstance;
	HWND_ptr _HWnd;
	//  World 와 소유권 공유중인 포인터
private:
	RECT _RectClient;
	RECT _RectWindow;
	
	MSG msg;
};

