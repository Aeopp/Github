#pragma once
#include "Device.h"
#include "Std.h"

class Window  : public  SingleTon<Window>
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	bool		m_bExit;
	RECT		m_rtWindow;

	HINSTANCE	hInstance ;
	HWND		hWnd ;
	RECT		ClientRect;
private:
	MSG			msg;
public:
	auto GetClientRT() {
		return ClientRect;
	}
	auto GetWindowRT() {
		return m_rtWindow;
	}
	bool SetWindow(HINSTANCE hInstance);
	bool WinRun();
	virtual LRESULT MsgProc(
		HWND hWnd,
		UINT msg,
		WPARAM wParam,
		LPARAM lParam);
	virtual bool GameRun();
public:
	 Window
	();
	virtual ~ Window
	();
};

