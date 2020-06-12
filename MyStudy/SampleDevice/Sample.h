#pragma once
#include <iostream>
#include <utility>
#include "Core.h"
#include "Mesh.h"

#include <string_view>

class Sample : public Core, public SingleTon<Sample>
{
public:
	Mesh m1;
	Write m_Write;

<<<<<<< HEAD
	bool Render(float DeltaTime)override; 
=======
	bool Render()override; 
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
	bool Init()override;
	bool Frame(float DeltaTime)override;
	bool Release()override; 
<<<<<<< HEAD
=======

	void    CreateDXResource() override;
	void    DeleteDXResource() override;
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
private:
	void PrintFont(const std::pair<FLOAT,FLOAT> Position,
	const std::wstring_view Text, const FLOAT fontSize = 50) & noexcept;

	DECLARE_SINGLETON(Sample)
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	if (Window::Instance().SetWindow(hInstance)) {
		Sample::Instance().Run();
	}
}

