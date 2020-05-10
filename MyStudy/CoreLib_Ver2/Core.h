#pragma once
#include "Window.h"
#include "SoundManager.h"
#include "Timer.h"
#include "InputManager.h"
#include "Actor.h"
class Engine : public Window
{
public:
	Timer		CurrentTimer;
	std::vector<std::shared_ptr<Actor>> Actors;
	std::shared_ptr<HDC__>ScreenHDC;
	std::shared_ptr<HDC__>OffScreenDC;
	std::unique_ptr<HFONT__,decltype(ObjectDeleter)> DefaultFont;
	std::unique_ptr<HFONT__, decltype(ObjectDeleter)> GameFont;
	std::unique_ptr<HBRUSH__, decltype(ObjectDeleter)>	BackGroundBrush;
	std::unique_ptr<HBITMAP__, decltype(ObjectDeleter)>	OffScreenBitmap;
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
	Engine();
	virtual ~Engine();
};

