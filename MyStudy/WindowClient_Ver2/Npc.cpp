#include "Npc.h"
bool TNpcObj::Frame()
{
	if (m_fPosY < 0.0f)
	{
		m_fPosY =0;
		fDirectionY *= -1.0f;
	}
	if( m_fPosY > World::ClientRect.bottom )
	{ 
		m_fPosY = 600;
		fDirectionY *= -1.0f;
	}
	if (m_fPosX < 0.0f)
	{
		m_fPosX = 0;
		fDirectionX *= -1.0f;
	}
	if (m_fPosX > World::ClientRect.right)
	{
		m_fPosX = 800;
		fDirectionX *= -1.0f;
	}
	m_fPosX += fDirectionX * World::FramePerSecond * 100.0f;
	m_fPosY += fDirectionY * World::FramePerSecond * 100.0f;

	SetPos(m_fPosX, m_fPosY);
	return true;
}
TNpcObj::TNpcObj()
{
	m_bDead = false;
}
TNpcObj::~TNpcObj()
{

}