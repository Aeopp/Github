#include "Core.h"
#include "SoundManager.h"
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
	// 해당 함수 호출이후 스왑체인 버퍼 스왑
	m_pSwapChain->Present(0, 0);
	return true;
}
bool Core::Release() { return true; }

bool Core::CoreInit()
{
	m_Timer.Init();
	I_Input.Init();	
	GetSound.Init();

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

	Init();
	return true;
}
bool Core::CoreFrame()
{
	m_Timer.Frame();
	I_Input.Frame();
	GetSound.Frame();

	if (I_Input.m_KeyState[DIK_ESCAPE] & 0x80) {
		m_bExit = true;
		return false;
	};

	Frame();
	return true;
}
bool Core::CoreRender()
{
	PreRender();
	Render();
	
	T_STR strBuffer = L"GameTime";
	strBuffer += m_Timer.m_csBuffer;
	m_Write.Draw(1, strBuffer.c_str(), m_rtClient);

	PostRender();
	return true;
}
bool Core::CoreRelease()
{
	Release();
	m_Timer.Release();
	I_Input.Release();
	GetSound.Release();

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