#pragma once
#include "Window.h"
#include "SoundManager.h"
#include "Timer.h"
#include "InputManager.h"
class TCore : public Window
{
public:
	Timer		m_Timer;

	HFONT		m_hDefaultFont;
	HFONT		m_hGameFont;
	HBRUSH		m_hbrBack;
	HDC			m_hScreenDC;
	HDC			m_hOffScreenDC;
	HBITMAP		m_hOffScreenBitmap;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
private:
	bool TCoreInit();
	bool TCoreFrame();
	bool TCoreRender();
	bool TCoreRelease();
public:
	bool TRun();
public:
	TCore();
	virtual ~TCore();
};

