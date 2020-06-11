#include "Input.h"
#include <algorithm>
POINT		 g_MousePos;

bool Input::Init()
{
	HRESULT hr = DirectInput8Create(g_hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDI, NULL);

	hr = m_pDI->CreateDevice(GUID_SysKeyboard, &m_pKey, NULL);
	hr = m_pDI->CreateDevice(GUID_SysMouse, &m_pMouse, NULL);

	m_pKey->SetDataFormat(&c_dfDIKeyboard);
	m_pMouse->SetDataFormat(&c_dfDIMouse);
	// 협조레벨
	
	hr = m_pKey->SetCooperativeLevel(g_hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY );
	hr = m_pMouse->SetCooperativeLevel(g_hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND | DISCL_NOWINKEY );
	while (m_pKey->Acquire() == DIERR_INPUTLOST);
	while (m_pMouse->Acquire() == DIERR_INPUTLOST);
	return true;
}
bool Input::Frame()
{
	HRESULT hr;
	GetCursorPos(&m_MousePos);// 스크린좌표
	ScreenToClient(g_hWnd, &m_MousePos);
	g_MousePos = m_MousePos;

	ZeroMemory(m_KeyState, sizeof(BYTE) * KeyNumber);

	if (FAILED(m_pKey->GetDeviceState(KeyNumber, m_KeyState)))
	{
		while (m_pKey->Acquire() == DIERR_INPUTLOST);
		m_pKey->Acquire();
	};

	for (uint32_t i = 0; i < KeyNumber; ++i) {
		bool bCurrentPress = m_KeyState[i] & 0x80;
		EKeyState& KeyState = CurrentKeyState[i];

		// T T 
		if (bCurrentPress == true && (KeyState == EKeyState::Press ||
			KeyState == EKeyState::Hold) ){
			KeyState = EKeyState::Hold;
		}
		// T F
		// 프레스 홀드 릴리즈 플 
		else if (bCurrentPress == true && (KeyState == EKeyState::Release ||
			KeyState == EKeyState::Free) ){
			KeyState = EKeyState::Press;
		}
		// F T
		else if (bCurrentPress == false && (KeyState == EKeyState::Press ||
			KeyState == EKeyState::Hold)) {
			KeyState = EKeyState::Release;
		}
		// F F
		else if (bCurrentPress == false && (KeyState == EKeyState::Release ||
			KeyState == EKeyState::Free)) {
			KeyState = EKeyState::Free;
		};
	};

	ZeroMemory(&m_MouseState, sizeof(DIMOUSESTATE));
	m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),
		&m_MouseState);
	if (FAILED(m_pMouse->GetDeviceState(sizeof(DIMOUSESTATE),
		&m_MouseState)))
	{
		while (m_pMouse->Acquire() == DIERR_INPUTLOST);
		m_pMouse->Acquire();
	}

	EventNotify(0);

	return true;
}
Input::Input() {
	std::fill_n(std::begin(CurrentKeyState), KeyNumber, EKeyState::Free);
};

bool Input::Release()
{
	if (m_pKey)
	{
		m_pKey->Unacquire();
		m_pKey->Release();
	}
	if (m_pMouse)
	{
		m_pMouse->Unacquire();
		m_pMouse->Release();
	}
	if (m_pDI) m_pDI->Release();
	return true;
}