#pragma once
#include <iostream>
#include "Core.h"

class Sample : public Core
{
public :
	bool Render()override; 
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample win;
	if (win.SetWindow(hInstance)) {
		win.Run();
	}
}

