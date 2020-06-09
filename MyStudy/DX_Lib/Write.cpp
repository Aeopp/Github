#include "Write.h"

void Write::Draw(UINT iSize, const TCHAR* szBuffer, RECT rt, D2D1::ColorF color)
{
	TextArray text;
	text.iSize = iSize;
	text.text = szBuffer;
	text.color = color;
	text.rt.left = rt.left;
	text.rt.top = rt.top;
	text.rt.right = rt.right;
	text.rt.bottom = rt.bottom;
	m_TextList.push_back(text);
}

bool Write::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&m_pD2DFactory);

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&m_pDWriteFactory);

	for (int iFont = 0; iFont < 3; iFont++)
	{
		hr = m_pDWriteFactory->CreateTextFormat(
			L"���", NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			10 + iFont * 10, L"ko-kr",
			&m_pTextFormat[iFont]);
	}

	m_pD2DFactory->GetDesktopDpi(&m_fDpiX, &m_fDpiY);

	m_fDpiX;
	m_fDpiY;

	return true;
}

bool Write::OnResize(IDXGISurface* pSurface)
{
	HRESULT hr;
	D2D1_RENDER_TARGET_PROPERTIES rtp;
	rtp.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	rtp.pixelFormat.format =
		DXGI_FORMAT_UNKNOWN;
	rtp.pixelFormat.alphaMode =
		D2D1_ALPHA_MODE_PREMULTIPLIED;
	rtp.dpiX = m_fDpiX;
	rtp.dpiY = m_fDpiY;
	rtp.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	rtp.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	// �ʼ� : D3D11_CREATE_DEVICE_BGRA_SUPPORT
	hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
		pSurface,
		&rtp,
		&m_pd2dRT);

	hr = m_pd2dRT->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Yellow),
		&m_pDefaultBrush);
	return true;
}

bool Write::Release()
{
	if (m_pDefaultBrush) m_pDefaultBrush->Release();
	if (m_pd2dRT) m_pd2dRT->Release();

	if (m_pTextFormat[0])m_pTextFormat[0]->Release();
	if (m_pTextFormat[1])m_pTextFormat[1]->Release();
	if (m_pTextFormat[2])m_pTextFormat[2]->Release();

	if (m_pDWriteFactory)m_pDWriteFactory->Release();
	if (m_pD2DFactory)m_pD2DFactory->Release();
	return true;
}

bool Write::Render()
{
	m_pd2dRT->BeginDraw();

	for (int i = 0; i < m_TextList.size(); i++)
	{
		m_pd2dRT->SetTransform(m_TextList[i].matrix);
		m_pDefaultBrush->SetColor(m_TextList[i].color);
		m_pd2dRT->DrawText(m_TextList[i].text.c_str(),
			m_TextList[i].text.size(),
			m_pTextFormat[m_TextList[i].iSize],
			m_TextList[i].rt,
			m_pDefaultBrush);
	}
	m_TextList.clear();
	m_pd2dRT->EndDraw();
	return true;
}

void Write::DeleteDXResource()
{
	if (m_pd2dRT) m_pd2dRT->Release();
	if (m_pDefaultBrush) m_pDefaultBrush->Release();
}

Write::Write()
{
	m_pDWriteFactory = nullptr;
	m_pD2DFactory = nullptr;
}

Write::~Write()
{
	Release();

}
