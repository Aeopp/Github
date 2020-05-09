#include "Bitmap.h"
bool	TBitmap::Frame()
{
	return true;
}
bool	TBitmap::Render()
{
	return true;
}
bool	TBitmap::Init()
{
	return true;
}
// DDB(DC):디바이스종속비트맵, DIB(독립비트맵)
bool	TBitmap::Load(HDC hScreenDC, tstring szLoadFileName)
{
	m_hScreenDC = hScreenDC;
	m_hBitmap = (HBITMAP)LoadImage(world::InstanceHandle,
		szLoadFileName.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}
bool	TBitmap::Release()
{
	DeleteObject(m_hBitmap);
	ReleaseDC(world::WindowHandle, m_hMemDC);
	return true;
}
TBitmap::TBitmap()
{

}

TBitmap::~TBitmap()
{

}