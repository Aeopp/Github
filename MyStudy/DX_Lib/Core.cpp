#include "Core.h"
#include "SoundManager.h"
#include "World.h"
// RTV 갱신에 따른 추가적인 생성 작업들.

// RTV 갱신에 따른 사전 소멸 작업들.

bool Core::Init() { return true; }
bool Core::Frame(float DeltaTime) { return true; }
bool Core::PreRender(float DeltaTime)
{
	float clearcolor[4] = { 1.f,0.45f,0.75f,1 };
	Device::Instance().m_pContext->ClearRenderTargetView(Device::Instance().m_pRTV, clearcolor);;
	World::Instance().Render(DeltaTime);

	return true;
}
bool Core::Render(float DeltaTime) { 
	return true; 
}
bool Core::PostRender(float DeltaTime)
{
	// 해당 함수 호출이후 스왑체인 버퍼 스왑
	Device::Instance().m_pSwapChain->Present(1, 0);
	return true;
}
bool Core::Release() { return true; }

bool Core::CoreInit()
{
	Timer::Instance().Init();
	Input::Instance().Init();	
	SoundManager::Instance().Init();
	World::Instance().Init();
	
	if (!Device::Instance().SetD3DDevice(
		Window::Instance().GetClientRT().right,
		Window::Instance().GetClientRT().bottom)) return false;

	HRESULT hr = Device::Instance().m_pGIFactory->MakeWindowAssociation(Window::Instance().m_hWnd,0);

	if (FAILED(hr)){
		return false;
	}

	Init();
	return true;
}
bool Core::CoreFrame(float DeltaTime)
{
	Timer::Instance().Frame();
	Input::Instance().Frame();
	SoundManager::Instance().Frame();
	World::Instance().Frame(DeltaTime);

	if (Input::Instance().m_KeyState[DIK_ESCAPE] & 0x80) {
		Window::Instance().m_bExit = true;
		return false;
	};

	Frame(DeltaTime);
	return true;
}
bool Core::CoreRender(float DeltaTime)
{
	PreRender(DeltaTime);
	Render(DeltaTime);
	PostRender(DeltaTime);
	return true;
}
bool Core::CoreRelease()
{
	Release();
	Timer::Instance().Release();
	Input::Instance().Release();
	SoundManager::Instance().Release();
	World::Instance().Release();
	Device::Instance().ReleaseDevice();
	return true;
}
bool Core::Run()
{
	CoreInit();
	while (Window::Instance().m_bExit == false)
	{
		if (Window::Instance().WinRun())
		{
			const float CurrentDeltaTime = Timer::Instance().GetDeltaTime();

			CoreFrame(CurrentDeltaTime);
			CoreRender(CurrentDeltaTime);
		}
	}
	CoreRelease();
	return true;
};

Core::Core()
{
	Window::Instance().m_bExit = false;
}
Core::~Core()
{

}