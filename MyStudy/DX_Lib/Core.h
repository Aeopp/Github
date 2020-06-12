#pragma once
#include "Window.h"
#include "Write.h"
#include "Timer.h"
#include "Input.h"

class Core 
{
public:
	virtual bool	Init();
	virtual bool	Frame(float DeltaTime);
	virtual bool	PreRender(float DeltaTime);
	virtual bool	Render(float DeltaTime);
	virtual bool	PostRender(float DeltaTime);
	virtual bool	Release();
private:
	bool CoreInit();
	bool CoreFrame(float DeltaTime);
	bool CoreRender(float DeltaTime);
	bool CoreRelease();
public:
	bool Run();
public:
	Core();
	virtual ~Core();
};

