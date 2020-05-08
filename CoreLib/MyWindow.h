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
	//  World �� ������ �������� ������
	HINSTANCE _HInstance;
	HWND _HWnd;
private:
	RECT _RectClient;
	RECT _RectWindow;
	MSG msg;
};

