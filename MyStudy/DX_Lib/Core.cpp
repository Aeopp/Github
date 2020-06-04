#include "Core.h"
bool Core::Init() { return true; }
bool Core::Frame() { return true; }
bool Core::PreRender()
{
	return true;
}
bool Core::Render() { return true; }
bool Core::PostRender()
{
	return true;
}
bool Core::Release() { return true; }

bool Core::CoreInit()
{
	//m_Timer.Init();
	//I_SoundMgr.Init();
	//I_Input.Init();	
	Init();
	return true;
}
bool Core::CoreFrame()
{
	/*m_Timer.Frame();
	I_SoundMgr.Frame();
	I_Input.Frame();

	if (g_InputMap.bExit == KEY_PUSH)
	{
		m_bExit = true;
		return false;
	}*/

	Frame();
	return true;
}
bool Core::CoreRender()
{
	PreRender();
	Render();

	/*m_Timer.Render();
	I_SoundMgr.Render();
	I_Input.Render();

	T_STR strBuffer = L"GameTime";
	strBuffer += m_Timer.m_csBuffer;
	SetTextColor(m_hOffScreenDC, RGB(255, 0, 0));
	SetBkColor(m_hOffScreenDC, RGB(0, 0, 255));
	SetBkMode(m_hOffScreenDC, TRANSPARENT);
	DrawText(m_hOffScreenDC, strBuffer.c_str(),
		-1, &g_rtClient,
		DT_LEFT | DT_VCENTER);*/

	PostRender();
	return true;
}
bool Core::CoreRelease()
{
	Release();
	//m_Timer.Release();
	//I_SoundMgr.Release();
	return true;
}
bool Core::Run()
{
	CoreInit();
	while (!m_bExit)
	{
		if (WinRun())
		{
			CoreFrame();
			CoreRender();
		}
	}
	CoreRelease();
	return true;
}
Core::Core()
{
	m_bExit = false;
}
Core::~Core()
{

}