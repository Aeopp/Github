#include "Core.h"
#include "SoundManager.h"
// RTV 갱신에 따른 추가적인 생성 작업들.
void	Core::CreateDXResource()
{
	
}
// RTV 갱신에 따른 사전 소멸 작업들.
void	Core::DeleteDXResource()
{
	
}
bool Core::Init() { return true; }
bool Core::Frame() { return true; }
bool Core::PreRender()
{
	float clearcolor[4] = { 1.f,0.45f,0.75f,1 };
	m_pContext->ClearRenderTargetView(m_pRTV, clearcolor);;
	return true;
}
bool Core::Render() { return true; }
bool Core::PostRender()
{
	// 해당 함수 호출이후 스왑체인 버퍼 스왑
	m_pSwapChain->Present(1, 0);
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

	HRESULT hr = m_pGIFactory->MakeWindowAssociation(m_hWnd,0);

	if (FAILED(hr)){
		return false;
	}

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
	while (m_bExit==false)
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