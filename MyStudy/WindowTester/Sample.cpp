#include <iostream>
#include "Tester.h"
#include "Dependency.h"

void Run() {};

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow)
{


	auto WndProc = [](
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
	};


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
		return 1;
	}

	// 2, 등록된 윈도우클래스로 윈도우 생성
	HWND hWnd = CreateWindowEx(0,
		L"KGCAWIN",
		L"SAMPLEWINDOW",
		WS_OVERLAPPEDWINDOW,
		100, 100, 300, 300,
		0, 0, hInstance, 0);

	if (hWnd == NULL) return 1;
	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			Run();
		}
	}
	return 0;
}

