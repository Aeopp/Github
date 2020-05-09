#pragma once
#include "Bitmap.h"
struct TPoint
{
	float x;
	float y;
};
class TObject
{
public:
	int			m_iIndex;
	TBitmap*	m_pBitmap;
	RECT		m_rtSrc;
	RECT		m_rtDesk;
	RECT		m_rtCollision;
	float		m_fPosX;
	float		m_fPosY;
public:
	void		SetPos(float x, float y);
	void		SetPos(TPoint pos);
	void		SetRect(RECT rtSrc, RECT rtDesk);
	bool		Load(HDC hScreenDC, tstring szFileName);
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render(HDC hOffScreenDC);
	virtual bool		Release();
public:
	TObject();
	virtual ~TObject();
};

