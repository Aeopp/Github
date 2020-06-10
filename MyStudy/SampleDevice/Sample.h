#pragma once
#include <iostream>
#include "Core.h"
#include "Mesh.h"

class Sample : public Core
{
public:
	Sample() {};


	Mesh m1;
	Mesh m2;


	bool Render()override; 
	bool Init()override;
	bool Frame()override;
	bool Release()override; 
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample win;
	if (win.SetWindow(hInstance)) {
		win.Run();
	}
}

