#include "Sample.h"
#include "SoundManager.h"
#include "DXGI.h"
#include "World.h"
#include "Object.h"
#include "Player.h"
#include "Timer.h"
#include <string_view>

<<<<<<< HEAD
#include <string>

=======
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
using namespace std::string_view_literals;

bool Sample::Render(float DeltaTime) {
	
    // Test Code
	{
		std::wstring DX11{ L"DirectX11" };
		m_Write.Draw(1, DX11.c_str(), RECT{ 250,250,999999,99999999 });
	}

	PrintFont({ 250,250 },L"qweqweqw"sv, 50.f);

	m1.Render(DeltaTime);

<<<<<<< HEAD
=======
	m1.Render();
	
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
	m_Write.Render();
	return true;
}

<<<<<<< HEAD
bool Sample::Release() {
	m1.Release();
	return true;
};

=======
bool Sample::Release(){
	m1.Release
	();
	return true; 
}
void Sample::CreateDXResource()
{
	IDXGISurface* pSurface = nullptr;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"


 void Sample::PrintFont(const std::pair<FLOAT, FLOAT> Position, const std::wstring_view Text, const FLOAT fontSize) & noexcept {
	//m_Write.SetTextLayout(Text.data());
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
<<<<<<< HEAD
bool Sample::Frame(float DeltaTime) {


	if (Input::Instance().m_KeyState[DIK_1] & 0x80);
	if (Input::Instance().m_MouseState.rgbButtons[1] & 0x80);
=======
bool Sample::Frame() {
	if (I_Input.m_KeyState[DIK_1] & 0x80);
	if (I_Input.m_MouseState.rgbButtons[1] & 0x80);

	m1.Frame
	();
	
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"

	m1.Frame(DeltaTime);

	return true;
};
bool Sample::Init() {
	Device::Instance().CreateDXResource
		= [this]() {
		IDXGISurface* pSurface = nullptr;
		Device::Instance().m_pSwapChain->GetBuffer(0,
			__uuidof(IDXGISurface),
			(void**)&pSurface);

		m_Write.OnResize(pSurface);

		if (pSurface) pSurface->Release();
	};

	Device::Instance().DeleteDXResource =
		[this]() {
		m_Write.DeleteDXResource();
	};

	{
		SoundManager::Instance().Load("../../MapleData/BGM/TimeGate.mp3");
		SoundManager::Instance().Load("../../MapleData/BGM/WhenTheMorningComess.mp3");

		Input::Instance().EventRegist([](float) {
			SoundManager::Instance().Play("../../MapleData/BGM/TimeGate.mp3");
			},
			EKeyState::Press, DIK_F1);

		Input::Instance().EventRegist([](float) {
			SoundManager::Instance().Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
			},
			EKeyState::Press, DIK_F2);

		auto Temp = [](float) {
			SoundManager::Instance().Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
			//MessageBox(g_hWnd, L"3������", L"3������", NULL);
		};
		Timer::Instance().EventRegist(Temp, Timer::ECategory::Once, 5.f);
	};

	IDXGISurface* pSurface = nullptr;
	Device::Instance().m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);

	m_Write.Init();
	m_Write.OnResize(pSurface);

	if (pSurface) pSurface->Release();

<<<<<<< HEAD
	World::Instance().CreateActor<Player>();



=======
	std::vector<P3VERTEX> vertices1{
		{-1.0f, 1.0f, 0.0f,1,1,1,1, 0.f, 0.0f},  // 0
		{0.0f, 1.f, 0.0f, 1,1,1,1, 1.f, 0.0f },// 1
		{	-1.0f, 0.0f, 0.0f,1,1,1,1, 0.f, 1.f},// 2

		{	0.0f, 1.f, 0.0f,1,1,1,1,  1.0f, 0.0f},// 0
		{0.0f, 0.0f, 0.0f, 1,1,1,1, 1.0f, 1.0f},// 1
		{-1.0f, 0.0f, 0.0f,1,1,1,1, 0.0f, 1.0f}// 2
	};

	m1.Create(m_pd3dDevice, m_pContext,L"../../MapleData/Lin.png"sv,vertices1.data(), 6);
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"

	
	return true;
};

Sample::Sample() {};
Sample::~Sample() noexcept{};
