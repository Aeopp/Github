#include "Actor.h"
#include "BitmapManager.h"
bool		Actor::Init()
{
	return true;
}
void		Actor::SetPos(TPoint pos)
{
	SetPos(pos.x, pos.y);
}
void		Actor::SetPos(float x, float y)
{
	m_rtDesk.left	= x;
	m_rtDesk.top	= y;
	m_fPosX			= x;
	m_fPosY			= y;
	m_rtCollision.left	= x;
	m_rtCollision.top	= y;
	m_rtCollision.right =
		m_rtCollision.left + m_rtDesk.right;
	m_rtCollision.bottom =
		m_rtCollision.top + m_rtDesk.bottom;
}
void		Actor::SetRect(RECT rtSrc, RECT rtDesk)
{
	m_rtSrc		= rtSrc;
	m_rtDesk	= rtDesk;
	SetPos(m_rtDesk.left, m_rtDesk.top);
}
bool		Actor::Load(HDC hScreenDC, tstring szFileName)
{
	if (auto  SharedBitmap = GetBitmapManager.Load(hScreenDC, szFileName).lock();
		SharedBitmap) {
		m_pBitmap=SharedBitmap;
		m_rtSrc.left = 0;
		m_rtSrc.top = 0;
		m_rtSrc.right = SharedBitmap->m_BmpInfo.bmWidth;
		m_rtSrc.bottom = SharedBitmap->m_BmpInfo.bmHeight;
		m_rtDesk.left = 0;
		m_rtDesk.top = 0;
		m_rtDesk.right = World::ClientRect.right - World::ClientRect.left;
		m_rtDesk.bottom = World::ClientRect.bottom - World::ClientRect.top;

		m_fPosX = 0;
		m_fPosY = 0;
		return true;
	}
	else return false;
}
bool		Actor::Render(HDC hOffScreenDC)
{
	if (auto SharedBitmap = m_pBitmap.lock();
		SharedBitmap)
	{
		BitBlt(hOffScreenDC,
			m_rtDesk.left,
			m_rtDesk.top,
			m_rtDesk.right,
			m_rtDesk.bottom,
			SharedBitmap->m_hMemDC,
			m_rtSrc.left,
			m_rtSrc.top, SRCCOPY);
		return true;
	}
};
bool		Actor::Frame()
{
	return true;
}
bool		Actor::Release()
{
	return true;
}
Actor::Actor()
{

}
Actor::~Actor()
{

}