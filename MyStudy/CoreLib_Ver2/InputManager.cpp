#include "InputManager.h"


bool InputManager::Frame() 
{
	GetCursorPos(&MousePosition);// ½ºÅ©¸°ÁÂÇ¥
	ScreenToClient(World::WindowHandle, &MousePosition);
	World::MousePosition = MousePosition;
	
	World::InputMapState.WKey = KeyCheck('W');
	World::InputMapState.SKey = KeyCheck('S');
	World::InputMapState.AKey = KeyCheck('A');
	World::InputMapState.DKey = KeyCheck('D');
	

	World::InputMapState.LeftClick = KeyCheck(VK_LBUTTON);
	World::InputMapState.RightClick = KeyCheck(VK_RBUTTON);
	World::InputMapState.MiddleClick = KeyCheck(VK_MBUTTON);
	World::InputMapState.Attack = World::InputMapState.LeftClick;
	World::InputMapState.Exit = KeyCheck(VK_ESCAPE);
	return true;
}
bool InputManager::Render() 
{
	return true;
}
EKeyState InputManager::KeyCheck(uint32_t Key)
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
InputManager::InputManager()
{
}
InputManager::~InputManager()noexcept
{

}