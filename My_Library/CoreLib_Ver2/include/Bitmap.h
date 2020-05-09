#pragma once
#include "Utility.h"
#include "Object.h"

class Bitmap : public Object
{
private:
	struct  DisplayHandleDeleter{
	/*	HWND& WindowHandle;
		DisplayHandleDeleter(HWND WindowHandle) :WindowHandle{ WindowHandle } {
		}*/
		void operator()(HDC DisplayHandle) {
				ReleaseDC(World::WindowHandle, DisplayHandle);
		};
	};
public:
	HBITMAP		m_hBitmap;
	HDC	m_hMemDC;
	std::unique_ptr<HDC__, DisplayHandleDeleter>	m_hScreenDC;
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
	DEFAULT_MOVE_COPY(Bitmap)
};

