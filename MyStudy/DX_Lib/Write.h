#pragma once
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <vector>
#include <string> 
#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"dwrite.lib")


struct TextArray {
	UINT iSize;
	D2D1_RECT_F rt;
	std::wstring text;
	D3DCOLORVALUE color;
	D2D1_MATRIX_3X2_F matrix;
	TextArray() {
		iSize = 0;
		matrix = D2D1::IdentityMatrix();
	}
};

class Write
{
public:
	std::vector<TextArray> m_TextList;
	void Draw(UINT iSize, const TCHAR* szBuffer, RECT rt,
		D2D1::ColorF color = D2D1::ColorF(1, 0, 0, 1));
public:
	ID2D1Factory* m_pD2DFactory;
	IDWriteFactory* m_pDWriteFactory;
	IDWriteTextFormat* m_pTextFormat[4];
	ID2D1RenderTarget* m_pd2dRT;
	ID2D1SolidColorBrush* m_pDefaultBrush;
	float m_fDpiX;
	float m_fDpiY;
	IDWriteTextLayout* m_pTextLayout; 
	bool SetTextLayout(const TCHAR* text);
public:
	bool	Init();
	bool	OnResize(IDXGISurface* pSurface);
	bool	Release();
	bool	Render();
	void	DeleteDXResource();
public:
	Write();
	~Write();
};

