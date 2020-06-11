#include "Sample.h"
#include "SoundManager.h"
#include "DXGI.h"

namespace Tag{
	#include "PS.shh"
	#include "VS.shh"
}
using namespace Tag;

bool Sample::Render() {
    // Test Code
	{
		std::wstring DX11{ L"DirectX11" };
		m_Write.Draw(1, DX11.c_str(), RECT{ 250,250,999999,99999999 });
	}

	PrintFont({ 250,250 }, m_Timer.m_csBuffer, 50.f);

	m1.Render();
	m2.Render();
	
	m_Write.Render();
	
	return true;
}

bool Sample::Release(){
	m1.Release
	();
	m2.Release();
	return true; 
}
void Sample::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);

	m_Write.OnResize(pSurface);

	if (pSurface) pSurface->Release();
}
void Sample::DeleteDXResource()
{
		m_Write.DeleteDXResource();
}
 void Sample::PrintFont(const std::pair<FLOAT, FLOAT> Position, const std::wstring_view Text, const FLOAT fontSize) & noexcept {
	m_Write.SetTextLayout(Text.data());
	D2D1_POINT_2F pos;
	pos.x = Position.first;
	pos.y = Position.second;

	m_Write.m_pd2dRT->BeginDraw();
	DWRITE_TEXT_RANGE range = { 0,wcslen(Text.data()) };
	m_Write.m_pTextLayout->SetFontSize(fontSize, range);
	m_Write.m_pTextLayout->SetUnderline(TRUE, range);
	m_Write.m_pTextLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, range);
	m_Write.m_pd2dRT->DrawTextLayout(pos,
		m_Write.m_pTextLayout,
		m_Write.m_pDefaultBrush);

	m_Write.m_pd2dRT->EndDraw();
}
bool Sample::Frame() {
	if (I_Input.m_KeyState[DIK_1] & 0x80)
	{
		int k = 0;
	}
	if (I_Input.m_MouseState.rgbButtons[1] & 0x80)
	{
		int k = 0;

	}

	m1.Frame
	();
	m2.Frame();


	return true;

};
bool Sample::Init() {
	GetSound.Load("../../MapleData/BGM/TimeGate.mp3");
	GetSound.Load("../../MapleData/BGM/WhenTheMorningComess.mp3");
	{
		I_Input.EventRegist([](float) {
			GetSound.Play("../../MapleData/BGM/TimeGate.mp3");
			},
			EKeyState::Press, DIK_F1);

		I_Input.EventRegist([](float) {
			GetSound.Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
			},
			EKeyState::Press, DIK_F2);
	};

	auto Temp = [](float) {
		GetSound.Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
	 	//MessageBox(g_hWnd, L"3초지남", L"3초지남", NULL);
	};

	{
		m_Timer.EventRegist(Temp,
			Timer::ECategory::Once, 5.f);
	}

	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);

	m_Write.Init();
	m_Write.OnResize(pSurface);

	if (pSurface) pSurface->Release();


	P3VERTEX vertices1[]{
		1,0, 0.0f,0,0,1,1,  // 0
		1,-1, 0.0f, 0,0,1,1,// 1
		0,-1	, 0.0f,0,0,1,1,// 2

		1,0, 0.0f,0,0,1,1,  // 0
		1,-1, 0.0f, 0,0,1,1,// 1
		0,-1	, 0.0f,0,0,1,1,// 2
	};

	m1.Create(m_pd3dDevice, m_pContext,
		vertices1, 6);

	P3VERTEX vertices2[] // 시계방향으로 
	{
		1,0, 0.0f,0,0,1,1,  // 0
		1,-1, 0.0f, 0,0,1,1,// 1
		0,-1	, 0.0f,0,0,1,1,// 2

		-1, 1, 0.0f,1,0,0,1,  // 0
		0,1, 0.0f, 1,0,0,1, // 1
		-1,0, 0.0f,1,0,0,1, // 2
	};

	m2.Create(m_pd3dDevice, m_pContext,
		vertices2, 6);

	return true;
};
