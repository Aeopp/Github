#pragma once
#include "Std.h"
class Window
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_bExit;
	RECT		m_rtClient;
	RECT		m_rtWindow;
private:
	MSG			msg;
public:
	bool SetWindow(HINSTANCE hInstance);
	bool WinRun();
	virtual bool GameRun();
public:
	 Window
	();
	virtual ~ Window
	();
};

