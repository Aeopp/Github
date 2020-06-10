#include "Sample.h"
#include "SoundManager.h"
bool Sample::Render() {
	m_Write.SetTextLayout(m_Timer.m_csBuffer);
	D2D1_POINT_2F pos;
	pos.x = 100;
	pos.y = 300;
	m_Write.m_pd2dRT->BeginDraw();
	DWRITE_TEXT_RANGE range = { 0, wcslen(m_Timer.m_csBuffer) };
	m_Write.m_pTextLayout->SetFontSize(50, range);
	m_Write.m_pTextLayout->SetUnderline(TRUE, range);
	m_Write.m_pTextLayout->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD, range);
	m_Write.m_pd2dRT->DrawTextLayout(pos,
		m_Write.m_pTextLayout,
		m_Write.m_pDefaultBrush);
	m_Write.m_pd2dRT->EndDraw();

	m1.Render();
	m2.Render();


	return true;
}

bool Sample::Release(){
	m1.Release
	();
	m2.Release();
	return true; 
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
	}
	auto Temp = [](float) {
	//	MessageBox(g_hWnd, L"3초지남", L"3초지남", NULL);
	};

	{
		m_Timer.EventRegist(Temp,
			Timer::ECategory::Loop, 3.f);
	}


	P3VERTEX vertices1[]{
		0,1, 0.0f,1,0,0,1,  // 0
		1,1, 0.0f, 1,0,0,1,// 1
		1,0, 0.0f,1,0,0,1,// 2

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
