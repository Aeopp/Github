#pragma once
#include <iostream>
#include <utility>
#include "Core.h"
#include "Mesh.h"
#include <string_view>

class Sample : public Core
{
public:
	Sample() {};

	Mesh m1;
	Mesh m2;
	Write m_Write;


	bool Render()override; 
	bool Init()override;
	bool Frame()override;
	bool Release()override; 

	void    CreateDXResource() override;
	void    DeleteDXResource() override;

private:
	void PrintFont(const std::pair<FLOAT,FLOAT> Position,
		const std::wstring_view Text, const FLOAT fontSize = 50) & noexcept;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	Sample win;
	if (win.SetWindow(hInstance)) {
		win.Run();
	}
}

