#pragma once
#include "Window.h"
#include "Write.h"
#include "Timer.h"
#include "Input.h"

class Core : public Window
{
public:
	Timer m_Timer;
public:
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	PreRender();
	virtual bool	Render();
	virtual bool	PostRender();
	virtual bool	Release();
	virtual void    CreateDXResource() override;
	virtual void    DeleteDXResource() override;
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

