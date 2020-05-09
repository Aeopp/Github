#pragma once
#include "Utility.h"
class Bitmap
{
public:
	HBITMAP		m_hBitmap;
	HDC			m_hMemDC;
	HDC			m_hScreenDC;
	BITMAP		m_BmpInfo;
	tstring		m_csName;
public:
	bool	Release();
	bool	Frame();
	bool	Render();
	bool	Init();
public:
	Bitmap(HDC hScreenDC, tstring szLoadFileName);
	~Bitmap();
};

