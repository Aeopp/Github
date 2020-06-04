#pragma once
#include "Window.h"
//#include "TSoundMgr.h"
//#include "TTimer.h"
//#include "TInput.h"
class Core : public Window
{
public:
	//TTimer		m_Timer;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
private:
	bool CoreInit();
	bool CoreFrame();
	bool CoreRender();
	bool CoreRelease();
public:
	bool Run();
public:
	Core();
	virtual ~Core();
};

