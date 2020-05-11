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

	_Sphere.Center.x = (Collision.right +  Collision.left)/2 ;
	_Sphere.Center.y = (Collision.bottom +  Collision.top) /2 ;
	const auto fLhs = Collision.right - _Sphere.Center.x;
	const auto fRhs  = 	Collision.bottom - _Sphere.Center.y;
	_Sphere.Radius = std::sqrt(fLhs* fLhs +fRhs*fRhs);
}
void		Actor::SetRect(RECT rtSrc, RECT rtDesk)
{
	RectSource = rtSrc;
	RectDestnation = rtDesk;
	SetPos(RectDestnation.left, RectDestnation.top);
};
bool		Actor::Load(std::shared_ptr<HDC__> hScreenDC, tstring szFileName)
{
	if (hScreenDC == nullptr)return false; 
	if (auto  SharedBitmap = GetBitmapManager.Load(hScreenDC, szFileName).lock();
		SharedBitmap) {
		BitmapPtr =SharedBitmap;
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
bool		Actor::Render(std::shared_ptr<HDC__> hOffScreenDC)
{
	if (auto SharedBitmap = BitmapPtr.lock();
		SharedBitmap)
	{
		BitBlt(hOffScreenDC.get(),
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
}
bool Actor::DrawColorKey(std::shared_ptr<HDC__> ScreenDC, COLORREF color)
{
	if (auto SharedBitmap = BitmapPtr.lock();
		SharedBitmap){
		TransparentBlt(ScreenDC.get(),
			RectDestnation.left,
			RectDestnation.top,
			RectDestnation.right,
			RectDestnation.bottom,
			SharedBitmap->MemoryHDC.get(),
			RectSource.left,
			RectSource.top,
			RectDestnation.right,
			RectDestnation.bottom,
			color);
		return true; 
	}
	else
		return false; 
}
;
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