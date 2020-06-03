#include "Window.h"
#include "Utility.h"

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
window::window()
{
	ZeroMemory(&_Message, sizeof(MSG));
}
window::~window()
{

}
bool window::GameRun() { return true; }
bool window::SetWindow(HINSTANCE hInstance)
{
	hInstance = std::shared_ptr<HINSTANCE__>(hInstance,[](auto){});
	World::hInstance = hInstance;
	// TODO:: 생성할 윈도우 클래스 등록
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
	// 2. 등록한 클래스로 실제 윈도우를 생성
	WindowHandle = std::shared_ptr<HWND__>(CreateWindowEx(0,
		WindowClassName,
		WindowName,
		WS_OVERLAPPEDWINDOW,//WS_POPUPWINDOW,//WS_OVERLAPPEDWINDOW,
		0, 
		0,
		ScreenSize.right-ScreenSize.left,
		ScreenSize.bottom- ScreenSize.top,
		0, 0, hInstance.get(), 0), [](auto) {});

	if (WindowHandle == NULL) return 1;
	
	GetClientRect(WindowHandle.get(), &ClientRect);
	GetWindowRect(WindowHandle.get(), &WindowRect);

	World::ClientRect = ClientRect;
	World::WindowHandle = WindowHandle;

	ShowWindow(WindowHandle.get(), SW_SHOW);
	return true;
}
bool window::WindowRun()
{	
	if (PeekMessage(&_Message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&_Message);
		DispatchMessage(&_Message);
		if (_Message.message == WM_QUIT)
		{
			Exit = true;
		}
		return false;
	}
	return true;
}
