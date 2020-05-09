#pragma once
#include "Utility.h"
#include "Object.h"
class Bitmap : public Object
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

