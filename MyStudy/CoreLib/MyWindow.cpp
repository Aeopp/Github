#include "MyWindow.h"

bool MyWindow::SetWindow(HINSTANCE hinstance) &
{
	this->hInstance = hinstance;
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
	{
		return false; 
	}
	this->hWnd = CreateWindowEx(0,
		L"KGCAWIN",
		L"SAMPLEMyWindow",
		WS_OVERLAPPEDWINDOW,
		100, 100, 300, 300, 0, 0, hInstance, 0);

	if (hWnd == NULL)return 1;
	ShowWindow(hWnd, SW_SHOW);
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


