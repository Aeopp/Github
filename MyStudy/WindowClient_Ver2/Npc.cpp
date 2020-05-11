#include "Npc.h"
#pragma comment(lib,"Msimg32.lib")
bool Npc::Frame()
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
bool Npc::Render(std::shared_ptr<HDC__> OffScreenDC)
{	
	if (auto SharedBitmap = BitmapPtr.lock();
		SharedBitmap)
	{
		TransparentBlt(OffScreenDC.get(),
			RectDestnation.left,
			RectDestnation.top,
			RectDestnation.right,
			RectDestnation.bottom,

			SharedBitmap->MemoryHDC.get(),
			RectSource.left,
			RectSource.top,
			RectDestnation.right,
			RectDestnation.bottom,
			RGB(000, 067, 171));
		return true;
	}else 
	return false; 
}
Npc::Npc()
{
	m_bDead = false;
}
Npc::~Npc()
{

}