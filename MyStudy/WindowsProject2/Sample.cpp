//#include "Sample.h"
//#include "SoundManager.h"
//#include "DXGI.h"
//#include "World.h"
//#include "Object.h"
//#include "Player.h"
//#include "Timer.h"
//#include <string_view>
//
//#include <string>
//
//
//bool Sample::Render(float DeltaTime) {
//	
//    // Test Code
//	{
//		std::wstring DX11{ L"DirectX11" };
//		m_Write.Draw(1, DX11.c_str(), RECT{ 250,250,999999,99999999 });
//	}
//
//	//PrintFont({ 250,250 },L"qweqweqw"sv, 50.f);
//
//	m1.Render(DeltaTime);
//
//	m_Write.Render();
//	return true;
//}
//
//bool Sample::Release() {
//	m1.Release();
//	return true;
//};
//
//
//
// void Sample::PrintFont(const std::pair<FLOAT, FLOAT> Position, const wchar_t* Text ,const FLOAT fontSize) & noexcept {
//	//m_Write.SetTextLayout(Text.data());
//	D2D1_POINT_2F pos;
//	pos.x = Position.first;
//	pos.y = Position.second;
//
//	m_Write.m_pd2dRT->BeginDraw();
//	DWRITE_TEXT_RANGE range = { 0,wcslen(Text) };
//	m_Write.m_pTextLayout->SetFontSize(fontSize, range);
//	m_Write.m_pTextLayout->SetUnderline(TRUE, range);
//	m_Write.m_pTextLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, range);
//	m_Write.m_pd2dRT->DrawTextLayout(pos,
//		m_Write.m_pTextLayout,
//		m_Write.m_pDefaultBrush);
//
//	m_Write.m_pd2dRT->EndDraw();
//}
//bool Sample::Frame(float DeltaTime) {
//
//
//	if (Input::Instance().m_KeyState[DIK_1] & 0x80);
//	if (Input::Instance().m_MouseState.rgbButtons[1] & 0x80);
//
//	m1.Frame(DeltaTime);
//
//	return true;
//};
//bool Sample::Init() {
//	Device::Instance().CreateDXResource
//		= [this]() {
//		IDXGISurface* pSurface = nullptr;
//		Device::Instance().m_pSwapChain->GetBuffer(0,
//			__uuidof(IDXGISurface),
//			(void**)&pSurface);
//
//		m_Write.OnResize(pSurface);
//
//		if (pSurface) pSurface->Release();
//	};
//
//	Device::Instance().DeleteDXResource =
//		[this]() {
//		m_Write.DeleteDXResource();
//	};
//
//	{
//		SoundManager::Instance().Load("../../MapleData/BGM/TimeGate.mp3");
//		SoundManager::Instance().Load("../../MapleData/BGM/WhenTheMorningComess.mp3");
//
//		Input::Instance().EventRegist([](float) {
//			SoundManager::Instance().Play("../../MapleData/BGM/TimeGate.mp3");
//			},
//			EKeyState::Press, DIK_F1);
//
//		Input::Instance().EventRegist([](float) {
//			SoundManager::Instance().Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
//			},
//			EKeyState::Press, DIK_F2);
//
//		auto Temp = [](float) {
//			SoundManager::Instance().Play("../../MapleData/BGM/WhenTheMorningComess.mp3");
//			//MessageBox(g_hWnd, L"3초지남", L"3초지남", NULL);
//		};
//		Timer::Instance().EventRegist(Temp, Timer::ECategory::Once, 5.f);
//	};
//
//	IDXGISurface* pSurface = nullptr;
//	Device::Instance().m_pSwapChain->GetBuffer(0,
//		__uuidof(IDXGISurface),
//		(void**)&pSurface);
//
//	m_Write.Init();
//	m_Write.OnResize(pSurface);
//
//	if (pSurface) pSurface->Release();
//
//	World::Instance().CreateActor<Player>();
//
//
//
//
//	
//	return true;
//};
//
//Sample::Sample() {};
//Sample::~Sample() noexcept{};
