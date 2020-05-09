#include "TObject.h"
#include "TBitmapMgr.h"
bool		TObject::Init()
{
	return true;
}
void		TObject::SetPos(TPoint pos)
{
	SetPos(pos.x, pos.y);
}
void		TObject::SetPos(float x, float y)
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
void		TObject::SetRect(RECT rtSrc, RECT rtDesk)
{
	m_rtSrc		= rtSrc;
	m_rtDesk	= rtDesk;
	SetPos(m_rtDesk.left, m_rtDesk.top);
}
bool		TObject::Load(HDC hScreenDC, T_STR szFileName)
{
	m_iIndex = I_BitmapMgr.Load(hScreenDC, szFileName);
	m_pBitmap = I_BitmapMgr.GetPtr(m_iIndex);
	m_rtSrc.left = 0;
	m_rtSrc.top = 0;
	m_rtSrc.right = m_pBitmap->m_BmpInfo.bmWidth;
	m_rtSrc.bottom = m_pBitmap->m_BmpInfo.bmHeight;
	m_rtDesk.left = 0;
	m_rtDesk.top = 0;
	m_rtDesk.right = g_rtClient.right - g_rtClient.left;
	m_rtDesk.bottom = g_rtClient.bottom - g_rtClient.top;

	m_fPosX = 0;
	m_fPosY = 0;
	return true;
}
bool		TObject::Render(HDC hOffScreenDC)
{
	BitBlt(hOffScreenDC,
			m_rtDesk.left,
			m_rtDesk.top, 
			m_rtDesk.right,
			m_rtDesk.bottom,
		m_pBitmap->m_hMemDC,
			m_rtSrc.left, 
			m_rtSrc.top, SRCCOPY);
	return true;
};
bool		TObject::Frame()
{
	return true;
}
bool		TObject::Release()
{
	return true;
}
TObject::TObject()
{

}
TObject::~TObject()
{

}