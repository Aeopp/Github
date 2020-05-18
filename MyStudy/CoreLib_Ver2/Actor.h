#pragma once
#include "Bitmap.h"
#include "Collision.h"
#include <valarray>
using FVector2D = std::valarray<float_t>;
class Actor
{
public:
	FVector2D Vector{ 0,0 };
	int			m_iIndex;
	std::weak_ptr<Bitmap>	BitmapPtr;
	std::weak_ptr<Bitmap>	BitmapMask;
	RECT		RectSource;
	RECT		RectDestnation;
	RECT		Collision;
	Sphere    _Sphere;
	float		X;
	float		Y;
public:
	void		SetPos(const float x,const float y);
	void		SetPos(FVector2D Pos);
	void		SetRect(RECT rtSrc, RECT rtDesk);
	bool		Load(std::shared_ptr<HDC__> hScreenDC, tstring Fullpath);
	void SetMaskBitmap(std::shared_ptr<HDC__> hScreenDC, tstring Filename); 
	virtual bool		Frame();
	virtual bool		Render(std::shared_ptr<HDC__> hOffScreenDC);
	bool DrawColorKey(std::shared_ptr<HDC__> ScreenDC, COLORREF color = RGB(000,067,171));
public:
	Actor();
	virtual ~Actor();
};

