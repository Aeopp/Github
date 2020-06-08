#include "Window.h"

HINSTANCE	g_hInstance = 0;
HWND		g_hWnd = 0;
RECT		g_rtClient;
Window* g_pWindow = nullptr;

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	assert(g_pWindow);
	return g_pWindow->MsgProc(hWnd, msg, wParam, lParam);
}
Window::Window()
{
	g_pWindow = this;

	ZeroMemory(&msg, sizeof(MSG));
}
Window::~Window()
{

}
bool Window::GameRun() { return true; }
bool Window::SetWindow(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	g_hInstance = hInstance;
	// 1, 생성할 윈도우클래스 운영체제 등록
	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEXW));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.hInstance = hInstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"KGCAWIN";
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	if (RegisterClassEx(&wc) == false)
	{
		return false;
	}
	RECT rt = { 0,0,800,600 };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, FALSE);
	// 2, 등록된 윈도우클래스로 윈도우 생성
	m_hWnd = CreateWindowEx(0,
		L"KGCAWIN",
		L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,
		0,
		0,
		rt.right - rt.left,
		rt.bottom - rt.top,
		0, 0, m_hInstance, 0);

	if (m_hWnd == NULL) return 1;

	GetClientRect(m_hWnd, &m_rtClient);
	GetWindowRect(m_hWnd, &m_rtWindow);

	g_rtClient = m_rtClient;
	g_hWnd = m_hWnd;

	ShowWindow(m_hWnd, SW_SHOW);
	return true;
}
bool Window::WinRun()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (msg.message == WM_QUIT)
		{
			m_bExit = true;
		}
		return false;
	}
	return true;
}

LRESULT Window::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
	{
		UINT width = LOWORD(lParam);
		UINT height = HIWORD(lParam);
		ResizeDevice(width, height);
		GetClientRect(m_hWnd, &m_rtClient);
		GetWindowRect(m_hWnd, &m_rtWindow);
		g_rtClient = m_rtClient;
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
