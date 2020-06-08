#include "Core.h"

// RTV 갱신에 따른 추가적인 생성 작업들.
void	Core::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();
}
// RTV 갱신에 따른 사전 소멸 작업들.
void	Core::DeleteDXResource()
{
	m_Write.DeleteDXResource();
}
bool Core::Init() { return true; }
bool Core::Frame() { return true; }
bool Core::PreRender()
{
	float clearcolor[4] = { 0.45f,0.45f,0.75f,1 };
	m_pContext->ClearRenderTargetView(m_pRTV, clearcolor);;
	return true;
}
bool Core::Render() { return true; }
bool Core::PostRender()
{
	m_Write.Render();
	m_pSwapChain->Present(0, 0);
	return true;
}
bool Core::Release() { return true; }

bool Core::CoreInit()
{
	//m_Timer.Init();
	//I_SoundMgr.Init();
	//I_Input.Init();	

	if (!SetD3DDevice(
		m_rtClient.right,
		m_rtClient.bottom)) return false;

	HRESULT hr = m_pGIFactory->MakeWindowAssociation(m_hWnd,
		DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER);
	if (FAILED(hr))
	{
		return false;
	}

	m_Write.Init();

	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
	m_Write.OnResize(pSurface);
	if (pSurface) pSurface->Release();

	//BOOL fullscreen;
	//m_pSwapChain->GetFullscreenState(&fullscreen, NULL);
	//m_pSwapChain->SetFullscreenState(!fullscreen, NULL);

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

	Device::ReleaseDevice();
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