#include "MyWindow.h"

bool MyWindow::SetWindow(HINSTANCE hinstance) &
{
	_HInstance = HINSTANCE_ptr(hinstance);
	world::HInstance=_HInstance;
	
	WNDCLASSEXW wc;
    ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.hInstance = hinstance;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"KGCAWIN";
	
	auto WndProc{ [](HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
	{
			switch (msg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			default :
				break;
			}
			return DefWindowProc(hWnd, msg, wParam, lParam); 
	} };
	
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(GRAY_BRUSH));

	if(RegisterClassEx(&wc)==false)
		return false; 
	
	
	_HWnd = HWND_ptr(CreateWindowEx(0,
		L"KGCAWIN",
		L"SAMPLEMyWindow",
		WS_OVERLAPPEDWINDOW,
		100, 100, 300, 300, 0, 0, world::HInstance.get(), 0));

	if (_HWnd == NULL)return false; 

	GetClientRect(_HWnd.get(), &_RectClient);
	GetWindowRect(_HWnd.get(), &_RectWindow);

	// 편의를 위해 소유권을 공유함
	world::RectClient = _RectClient;
	world::HWnd = _HWnd;
	
	ShowWindow(_HWnd.get(), SW_SHOW);
	return true; 
}

bool MyWindow::WinRun() &
{
	if(PeekMessage (&msg,nullptr,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if(msg.message ==WM_QUIT)
		{
			this->IsExit = true; 
		} 
		return false; 
	}
	return true; 
}

bool MyWindow::GameRun()&
{
	return true;  
}

MyWindow::MyWindow()
{
	 ZeroMemory(&msg, sizeof(MSG)); 
}


