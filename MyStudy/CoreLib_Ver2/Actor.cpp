#include "Actor.h"
#include "BitmapManager.h"

void		Actor::SetPos(FVector2D pos)
{
	Vector = std::move(pos);
}
void		Actor::SetPos(float x, float y)
{
	RectDestnation.left	= x;
	RectDestnation.top	= y;
	X			= x;
	Y			= y;
	Collision.left	= x;
	Collision.top	= y;
	Collision.right =
		Collision.left + RectDestnation.right;
	Collision.bottom =
		Collision.top + RectDestnation.bottom;
}
void		Actor::SetRect(RECT rtSrc, RECT rtDesk)
{
	RectSource		= rtSrc;
	RectDestnation	= rtDesk;
	SetPos(RectDestnation.left, RectDestnation.top);
}
bool		Actor::Load(HDC hScreenDC, tstring szFileName)
{
	if (auto  SharedBitmap = GetBitmapManager.Load(hScreenDC, szFileName).lock();
		SharedBitmap) {
		Bitmap=SharedBitmap;
		RectSource.left = 0;
		RectSource.top = 0;
		RectSource.right = SharedBitmap->BmpInfomation.bmWidth;
		RectSource.bottom = SharedBitmap->BmpInfomation.bmHeight;
		RectDestnation.left = 0;
		RectDestnation.top = 0;
		RectDestnation.right = World::ClientRect.right - World::ClientRect.left;
		RectDestnation.bottom = World::ClientRect.bottom - World::ClientRect.top;

		X = 0;
		Y = 0;
		return true;
	}
	else return false;
}
bool		Actor::Render(HDC hOffScreenDC)
{
	if (auto SharedBitmap = Bitmap.lock();
		SharedBitmap)
	{
		BitBlt(hOffScreenDC,
			RectDestnation.left,
			RectDestnation.top,
			RectDestnation.right,
			RectDestnation.bottom,
			SharedBitmap->MemoryHDC.get(),
			RectSource.left,
			RectSource.top, SRCCOPY);
		return true;
	}
	else return false;
};
bool		Actor::Frame()
{
	return true;
}

Actor::Actor()
{

}
Actor::~Actor()
{

}