#include "Bitmap.h"
bool	Bitmap::Frame()
{
	return true;
}
bool	Bitmap::Render()
{
	return true;
}
bool	Bitmap::Init()
{
	return true;
}
// DDB(DC):디바이스종속비트맵, DIB(독립비트맵)
bool	Bitmap::Release()
{
	DeleteObject(m_hBitmap);
	ReleaseDC(World::WindowHandle, m_hMemDC);
	return true;
}
Bitmap::Bitmap(HDC hScreenDC, tstring szLoadFileName)
{
	m_hScreenDC = hScreenDC;
	m_hBitmap = (HBITMAP)LoadImage(World::InstanceHandle,
		szLoadFileName.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);
	GetObject(m_hBitmap, sizeof(BITMAP), &m_BmpInfo);
	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
}

Bitmap::~Bitmap()
{

}