#include "TWindow.h"
#include "TStd.h"
HWND		g_hWnd = 0;
RECT		g_rtClient;

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
Window::Window()
{
	ZeroMemory(&_Message, sizeof(MSG));
}
Window::~Window()
{

}
bool Window::GameRun() { return true; }
bool Window::SetWindow(HINSTANCE hInstance)
{
	InstanceHandle = hInstance;
	world::InstanceHandle = hInstance;
	// TODO:: ������ ������ Ŭ���� ���
	auto WindowClassName  = L"WINDOW";
	auto WindowName = L"WINDOW_GAME";
	WNDCLASSEXW WindowClass;
	ZeroMemory(&WindowClass, sizeof(WNDCLASSEXW));
	WindowClass.cbSize = sizeof(WNDCLASSEXW);
	WindowClass.hInstance = hInstance;
	WindowClass.style = CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpszClassName = WindowClassName;
	WindowClass.lpfnWndProc = WndProc;
	WindowClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));
	if (RegisterClassEx(&WindowClass) == false)
	{
		return false;
	}
	RECT ScreenSize = { 0,0,800,600 };
	AdjustWindowRect(&ScreenSize, WS_OVERLAPPEDWINDOW, FALSE);
	// 2. ����� Ŭ������ ���� �����츦 ����
	WindowHandle = CreateWindowEx(0,
		WindowClassName,
		WindowName,
		WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,
		0, 
		0,
		ScreenSize.right-ScreenSize.left,
		ScreenSize.bottom- ScreenSize.top,
		0, 0, InstanceHandle, 0);

	if (WindowHandle == NULL) return 1;
	
	GetClientRect(WindowHandle, &ClientRect);
	GetWindowRect(WindowHandle, &WindowRect);

	g_rtClient = ClientRect;
	g_hWnd = WindowHandle;

	ShowWindow(WindowHandle, SW_SHOW);
	return true;
}
bool Window::WindowRun()
{	
	if (PeekMessage(&_Message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&_Message);
		DispatchMessage(&_Message);
		if (_Message.message == WM_QUIT)
		{
			bExit = true;
		}
		return false;
	}
	return true;
}
