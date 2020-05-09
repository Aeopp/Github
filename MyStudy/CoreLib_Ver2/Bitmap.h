#pragma once
#include "Utility.h"
class TBitmap
{
public:
	HBITMAP		m_hBitmap;
	HDC			m_hMemDC;
	HDC			m_hScreenDC;
	BITMAP		m_BmpInfo;
	tstring		m_csName;
public:
	bool	Load(HDC hScreenDC, tstring szName);
	bool	Release();
	bool	Frame();
	bool	Render();
	bool	Init();
public:
	TBitmap();
	~TBitmap();
};

