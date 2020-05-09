#include "Hero.h"
#include "InputManager.h"
bool THeroObj::Frame()
{
	if (GetInputManager.KeyCheck('W')==EKeyState::Push || 
		GetInputManager.KeyCheck('W') == EKeyState::Hold)
	{
		m_fPosY-= World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('S') == EKeyState::Push || 
		GetInputManager.KeyCheck('S') == EKeyState::Hold)
	{
		m_fPosY += World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('A') == EKeyState::Push ||
		GetInputManager.KeyCheck('A') == EKeyState::Hold)
	{
		m_fPosX -= World::FramePerSecond * m_fSpeed;
	}
	if (GetInputManager.KeyCheck('D') == EKeyState::Push ||
		GetInputManager.KeyCheck('D') == EKeyState::Hold)
	{
		m_fPosX += World::FramePerSecond * m_fSpeed;
	}
	SetPos(m_fPosX, m_fPosY);
	return true;
}
THeroObj::THeroObj()
{
	m_fSpeed = 200.0f;
}
THeroObj::~THeroObj()
{

}