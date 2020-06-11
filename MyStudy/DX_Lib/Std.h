#pragma once
#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <list>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <set>
#include <assert.h>
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <type_traits>

#pragma warning( disable : 26812 )
#pragma warning( disable : 4005)

// 널검사
template<typename _ptrType>
bool constexpr IsValid(_ptrType ptr) {
	static_assert(std::is_pointer_v < _ptrType > == true && L"is not pointer type");
	return (ptr != nullptr);
};

template<typename ..._DX_PTR_TYPE>
void DX_CheckValidRelease(_DX_PTR_TYPE&&... ptrs) {
	static auto CheckRelease=
	[](auto ptr) noexcept {
		if (IsValid(ptr)) {
			ptr->Release();
		}
	}; 

	(CheckRelease(ptrs),...);
}

//추가종속성 winmm.lib; fmod_vc.lib; TCoreLib.lib;
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "CoreDx_d.lib")
#pragma comment (lib, "fmod_vc.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

// DirectX Utility
#if defined(_DEBUG)
	#pragma comment (lib, "d3dx11d.lib")
#else
	#pragma comment (lib, "d3dx11.lib")
#endif 

extern float		g_fSecondPerFrame;
extern float		g_fTimer;
extern HINSTANCE	g_hInstance;
extern HWND			g_hWnd;
extern RECT			g_rtClient;
extern POINT		g_MousePos;

// Singleton
template <class T>
class Singleton
{
public://TSoundMgr': private 멤버 -> friend
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}
};
//
//#ifndef SAFE_NEW
//#define SAFE_NEW(A,B)  {if(!A) A= new B;}
//#endif // !SAFE_NEW
//
//#ifndef SAFE_DEL
//#define SAFE_DEL(A)    {if(A) delete A; (A) = 0;}
//#endif // !SAFE_DEL
//
//
//#ifndef SAFE_ZERO
//#define SAFE_ZERO(A)    {(A) = 0;}
//#endif // !SAFE_DEL

//
//#define CORE_START void main() {
//#define CORE_RUN 	Sample sample;sample.Run();
//#define CORE_END }
//#define GAME CORE_START;CORE_RUN;CORE_END;
//
//#define WINCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow){
//#define WINCORE_RUN 	Sample win;if(win.SetWindow(hInstance)){win.Run();}
//#define WINCORE_END }
//#define WINGAME WINCORE_START;WINCORE_RUN;WINCORE_END;
//
