#pragma once
#include "TStd.h"
class TBitmap
{
public:
	HBITMAP		m_hBitmap;
	HDC			m_hMemDC;
	HDC			m_hScreenDC;
	BITMAP		m_BmpInfo;
	T_STR		m_csName;
public:
	bool	Load(HDC hScreenDC, T_STR szName);
	bool	Release();
	bool	Frame();
	bool	Render();
	bool	Init();
public:
	TBitmap();
	~TBitmap();
};

