#pragma once
#include "Bitmap.h"
#include <valarray>
using FVector2D = std::valarray<float_t>;
class Actor
{
public:
	FVector2D Vector{ 0,0 };
	int			m_iIndex;
	std::weak_ptr<Bitmap>	Bitmap;
	RECT		RectSource;
	RECT		RectDestnation;
	RECT		Collision;
	float		X;
	float		Y;
public:
	void		SetPos(float x, float y);
	void		SetPos(FVector2D pos);
	void		SetRect(RECT rtSrc, RECT rtDesk);
	bool		Load(std::shared_ptr<HDC__> hScreenDC, tstring Fullpath);
	virtual bool		Frame();
	virtual bool		Render(std::shared_ptr<HDC__> hOffScreenDC);
public:
	Actor();
	virtual ~Actor();
};

