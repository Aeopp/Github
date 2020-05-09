#include "Hero.h"
#include "InputManager.h"
bool Hero::Frame()
{
	if (GetInputManager.KeyCheck('W')==EKeyState::Push || 
		GetInputManager.KeyCheck('W') == EKeyState::Hold)
	{
		Vector[1]-= World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('S') == EKeyState::Push || 
		GetInputManager.KeyCheck('S') == EKeyState::Hold)
	{
		Vector[1] += World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('A') == EKeyState::Push ||
		GetInputManager.KeyCheck('A') == EKeyState::Hold)
	{
		Vector[0] -= World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('D') == EKeyState::Push ||
		GetInputManager.KeyCheck('D') == EKeyState::Hold)
	{
		Vector[0] += World::FramePerSecond * m_fSpeed;
	}
	SetPos(Vector[0],Vector[1]);
	return true;
}
Hero::Hero()
{
	m_fSpeed = 200.0f;
}
Hero::~Hero()
{

}