#pragma once
#include "Core.h"

class Sample : public Core
{
public :
	bool Init() {
		return true;
	}
	bool Render() { return true; };

	bool Release() { return true; };
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample win;
	if (win.SetWindow(hInstance)) {
		win.Run();
	}
}

