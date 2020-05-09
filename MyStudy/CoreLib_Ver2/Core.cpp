#include "Core.h"
bool Engine::Init() { return true; }
bool Engine::Frame() { return true; }
bool Engine::PreRender() 
{ 	
	PatBlt( m_hOffScreenDC, 
			0, 0, ClientRect.right, 
			ClientRect.bottom, 
			PATCOPY);
	return true; 
}
bool Engine::Render() { return true; }
bool Engine::PostRender() 
{ 
	BitBlt(ScreenHDC, 0, 0, ClientRect.right, ClientRect.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true; 
}
bool Engine::Release() { return true; }

bool Engine::TCoreInit()
{	
	ScreenHDC = GetDC(WindowHandle);
	m_hOffScreenDC = CreateCompatibleDC(ScreenHDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		ScreenHDC, ClientRect.right, ClientRect.bottom);
	
	COLORREF bkColor = RGB(255, 0, 0);
	m_hbrBack = CreateSolidBrush(bkColor);	

	m_hDefaultFont = CreateFont(
		20, 0, 0, FW_BOLD, 0,0,0,0,
		HANGEUL_CHARSET, 0,0,0,
		0,//VARIABLE_PITCH | FF_ROMAN, 
		L"±Ã¼­");
	m_hGameFont = CreateFont(
		30, 0, 0, FW_BOLD, 0, 0, 0, 0,
		DEFAULT_CHARSET, 0, 0, 0,
		0,//VARIABLE_PITCH | FF_ROMAN, 
		L"°íµñ");
	
	SelectObject(m_hOffScreenDC, m_hbrBack);
	SelectObject(m_hOffScreenDC, m_hDefaultFont);
	SelectObject(m_hOffScreenDC, m_hOffScreenBitmap);


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
		SetTextColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetBkColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		DrawText(m_hOffScreenDC, strBuffer.c_str(),
			-1, &World::ClientRect,
			DT_LEFT | DT_VCENTER);

	PostRender();
	return true;
}
bool Engine::TCoreRelease()
{
	Release();

	DeleteObject(m_hDefaultFont);
	DeleteObject(m_hGameFont);
	DeleteObject(m_hbrBack);
	DeleteObject(m_hOffScreenBitmap);
	ReleaseDC(WindowHandle, m_hOffScreenDC);
	ReleaseDC(WindowHandle, ScreenHDC);


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