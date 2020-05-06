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
	//  World �� ������ �������� ������
	HINSTANCE_ptr _HInstance;
	HWND_ptr _HWnd;
	//  World �� ������ �������� ������
private:
	RECT _RectClient;
	RECT _RectWindow;
	
	MSG msg;
};

