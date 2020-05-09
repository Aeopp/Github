#include "InputManager.h"
POINT  g_MousePos;
InputActionMap  g_InputMap;


bool TInput::Frame() 
{
	GetCursorPos(&MousePosition);// ½ºÅ©¸°ÁÂÇ¥
	ScreenToClient(World::WindowHandle, &MousePosition);
	g_MousePos = MousePosition;
	
	g_InputMap.WKey = KeyCheck('W');
	g_InputMap.SKey = KeyCheck('S');
	g_InputMap.AKey = KeyCheck('A');
	g_InputMap.DKey = KeyCheck('D');
	

	g_InputMap.LeftClick = KeyCheck(VK_LBUTTON);
	g_InputMap.RightClick = KeyCheck(VK_RBUTTON);
	g_InputMap.MiddleClick = KeyCheck(VK_MBUTTON);
	g_InputMap.Attack = g_InputMap.LeftClick;
	g_InputMap.Exit = KeyCheck(VK_ESCAPE);
	return true;
}
bool TInput::Render() 
{
	return true;
}
EKeyState TInput::KeyCheck(uint32_t Key)
{
	SHORT KeyState = GetAsyncKeyState(Key);
	// 0x8000 -> 10000000 00000000
	if (KeyState & 0x8000)
	{
		if (KeyStates[Key] == EKeyState::Free ||
			KeyStates[Key] == EKeyState::Up)
		{
			KeyStates[Key] = EKeyState::Push;
		}
		else
		{
			KeyStates[Key] = EKeyState::Hold;
		}
	}
	else
	{
		if (KeyStates[Key] == EKeyState::Push ||
			KeyStates[Key] == EKeyState::Hold)
		{
			KeyStates[Key] = EKeyState::Up;
		}
		else
		{
			KeyStates[Key] = EKeyState::Free;
		}
	}
	return KeyStates[Key];
}
TInput::TInput()
{
}
TInput::~TInput()
{

}