#include "Hero.h"
#include "InputManager.h"
bool THeroObj::Frame()
{
	if (I_Input.KeyCheck('W'))
	{
		m_fPosY-= world::FramePerSecond * m_fSpeed;
	}
	if (I_Input.KeyCheck('S'))
	{
		m_fPosY += world::FramePerSecond * m_fSpeed;
	}
	if (I_Input.KeyCheck('A'))
	{
		m_fPosX -= world::FramePerSecond * m_fSpeed;
	}
	if (I_Input.KeyCheck('D'))
	{
		m_fPosX += world::FramePerSecond * m_fSpeed;
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