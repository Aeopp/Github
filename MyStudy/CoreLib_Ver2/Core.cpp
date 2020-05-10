#include "Core.h"
bool Engine::Frame() { return true; }
bool Engine::PreRender() 
{ 	
	PatBlt( OffScreenDC.get(),
			0, 0, ClientRect.right, 
			ClientRect.bottom, 
			PATCOPY);
	return true; 
}
bool Engine::Render() { return true; }
bool Engine::PostRender() 
{ 
	BitBlt(ScreenHDC.get(), 0, 0, ClientRect.right, ClientRect.bottom,
		OffScreenDC.get(), 0, 0, SRCCOPY);
	return true; 
}
bool Engine::Release() { return true; }
bool Engine::Init() { return true; }
bool Engine::TCoreInit()
{	
	ScreenHDC = std::shared_ptr<HDC__>(GetDC(WindowHandle), HDCReleaseDC);
	OffScreenDC = std::shared_ptr<HDC__>(CreateCompatibleDC(ScreenHDC.get()),HDCDeleteDC);
	OffScreenBitmap = std::unique_ptr<HBITMAP__, decltype(ObjectDeleter)>(
	CreateCompatibleBitmap(ScreenHDC.get(), ClientRect.right, ClientRect.bottom),ObjectDeleter);
	
	COLORREF bkColor = RGB(255, 0, 0);
	BackGroundBrush = std::unique_ptr<HBRUSH__, decltype(ObjectDeleter)>
	(CreateSolidBrush(bkColor),ObjectDeleter);

	DefaultFont = std::unique_ptr<HFONT__, decltype(ObjectDeleter)>(CreateFont(
		20, 0, 0, FW_BOLD, 0, 0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0,
		0,//VARIABLE_PITCH | FF_ROMAN, 
		L"±Ã¼­"), ObjectDeleter);
	GameFont = std::unique_ptr<HFONT__, decltype(ObjectDeleter)>(CreateFont(
		30, 0, 0, FW_BOLD, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0,
		0,//VARIABLE_PITCH | FF_ROMAN, 
		L"°íµñ"),ObjectDeleter);
	
	SelectObject(OffScreenDC.get(), BackGroundBrush.get());
	SelectObject(OffScreenDC.get(), DefaultFont.get());
	SelectObject(OffScreenDC.get(), OffScreenBitmap.get());
	Init();
	return true;
}
bool Engine::TCoreFrame()
{
	CurrentTimer.Frame();
	GetSoundManager.Frame();
	GetInputManager.Frame();

	if (World::InputMapState.Exit == EKeyState::Push)
	{
		Exit = true;
		return false;
	}

	Frame();
	return true;
}
bool Engine::TCoreRender()
{
	PreRender();
		Render();

		CurrentTimer.Render();
		GetSoundManager.Render();
		GetInputManager.Render();

		tstring strBuffer = L"GameTime";
		strBuffer += CurrentTimer.TimeOutputString;
		SetTextColor(OffScreenDC.get(), RGB(255, 0, 0));
		SetBkColor(OffScreenDC.get(), RGB(0, 0, 255));
		SetBkMode(OffScreenDC.get(), TRANSPARENT);
		DrawText(OffScreenDC.get(), strBuffer.c_str(),
			-1, &World::ClientRect,
			DT_LEFT | DT_VCENTER);

	PostRender();
	return true;
}
bool Engine::TCoreRelease()
{
	Release();

	GetSoundManager.Clear();
	return true;
}
bool Engine::TRun()
{
	TCoreInit();
	while (!Exit)
	{
		if (WindowRun())
		{
			TCoreFrame();
			TCoreRender();
			Sleep(1);
		}
	}
	TCoreRelease();
	return true;
}
Engine::Engine()
{
	Exit = false;
}
Engine::~Engine()
{

}