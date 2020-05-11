#include "Hero.h"
#include "InputManager.h"
bool Hero::Frame()
{
	if (GetInputManager.KeyCheck('W')==EKeyState::Push || 
		GetInputManager.KeyCheck('W') == EKeyState::Hold)
	{
		Vector[1]-= World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('S') == EKeyState::Push || 
		GetInputManager.KeyCheck('S') == EKeyState::Hold)
	{
		Vector[1] += World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('A') == EKeyState::Push ||
		GetInputManager.KeyCheck('A') == EKeyState::Hold)
	{
		Vector[0] -= World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('D') == EKeyState::Push ||
		GetInputManager.KeyCheck('D') == EKeyState::Hold)
	{
		Vector[0] += World::FramePerSecond * Speed;
	}
	SetPos(Vector[0],Vector[1]);
	return true;
}
Hero::Hero()
{
	Speed = 200.0f;
}
Hero::~Hero()
{

}