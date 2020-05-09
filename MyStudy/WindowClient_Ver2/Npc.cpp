#include "Npc.h"
bool TNpcObj::Frame()
{
	if (Y < 0.0f)
	{
		Y =0;
		fDirectionY *= -1.0f;
	}
	if( Y > World::ClientRect.bottom )
	{ 
		Y = 600;
		fDirectionY *= -1.0f;
	}
	if (X < 0.0f)
	{
		X = 0;
		fDirectionX *= -1.0f;
	}
	if (X > World::ClientRect.right)
	{
		X = 800;
		fDirectionX *= -1.0f;
	}
	X += fDirectionX * World::FramePerSecond * 100.0f;
	Y += fDirectionY * World::FramePerSecond * 100.0f;

	SetPos(X, Y);
	return true;
}
TNpcObj::TNpcObj()
{
	m_bDead = false;
}
TNpcObj::~TNpcObj()
{

}