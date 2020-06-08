#pragma once
#include <iostream>
 #include "Core.h"

class Sample : public Core
{

};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample win;
	if (win.SetWindow(hInstance)) {
		win.Run();
	}
}

