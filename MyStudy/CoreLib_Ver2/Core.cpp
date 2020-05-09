#include "Core.h"
bool TCore::Init() { return true; }
bool TCore::Frame() { return true; }
bool TCore::PreRender() 
{ 	
	PatBlt( m_hOffScreenDC, 
			0, 0, ClientRect.right, 
			ClientRect.bottom, 
			PATCOPY);
	return true; 
}
bool TCore::Render() { return true; }
bool TCore::PostRender() 
{ 
	BitBlt(m_hScreenDC, 0, 0, ClientRect.right, ClientRect.bottom,
		m_hOffScreenDC, 0, 0, SRCCOPY);
	return true; 
}
bool TCore::Release() { return true; }

bool TCore::TCoreInit()
{	
	I_SoundMgr.Init();
	I_Input.Init();

	m_hScreenDC = GetDC(WindowHandle);
	m_hOffScreenDC = CreateCompatibleDC(m_hScreenDC);
	m_hOffScreenBitmap = CreateCompatibleBitmap(
		m_hScreenDC, ClientRect.right, ClientRect.bottom);
	
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
bool TCore::TCoreFrame()
{
	m_Timer.Frame();
	I_SoundMgr.Frame();
	I_Input.Frame();

	if (g_InputMap.bExit == KEY_PUSH)
	{
		bExit = true;
		return false;
	}

	Frame();
	return true;
}
bool TCore::TCoreRender()
{
	PreRender();
		Render();

		m_Timer.Render();
		I_SoundMgr.Render();
		I_Input.Render();	

		tstring strBuffer = L"GameTime";
		strBuffer += m_Timer.TimeOutputString;
		SetTextColor(m_hOffScreenDC, RGB(255, 0, 0));
		SetBkColor(m_hOffScreenDC, RGB(0, 0, 255));
		SetBkMode(m_hOffScreenDC, TRANSPARENT);
		DrawText(m_hOffScreenDC, strBuffer.c_str(),
			-1, &world::ClientRect,
			DT_LEFT | DT_VCENTER);

	PostRender();
	return true;
}
bool TCore::TCoreRelease()
{
	Release();

	DeleteObject(m_hDefaultFont);
	DeleteObject(m_hGameFont);
	DeleteObject(m_hbrBack);
	DeleteObject(m_hOffScreenBitmap);
	ReleaseDC(WindowHandle, m_hOffScreenDC);
	ReleaseDC(WindowHandle, m_hScreenDC);


	I_SoundMgr.Release();
	return true;
}
bool TCore::TRun()
{
	TCoreInit();
	while (!bExit)
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
TCore::TCore()
{
	bExit = false;
}
TCore::~TCore()
{

}