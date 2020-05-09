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
using namespace std;
typedef basic_string<TCHAR> T_STR;
//using T_STR = basic_string <TCHAR>;
typedef basic_string<char>  C_STR;
typedef basic_string<wchar_t> W_STR;
typedef std::vector<T_STR> T_STR_VECTOR;

//추가종속성 winmm.lib; fmod_vc.lib; TCoreLib.lib;
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "fmod_vc.lib")

class world {
public:
	static inline HINSTANCE InstanceHandle = nullptr;
	static inline HWND WindowHandle = nullptr;
	static inline RECT ClientRect; 
};
struct TInputActionMap
{
	DWORD bAttack;
	DWORD bJump;
	DWORD bExit;

	DWORD bWKey;
	DWORD bSKey;
	DWORD bAKey;
	DWORD bDKey;

	DWORD bLeftClick;
	DWORD bRightClick;
	DWORD bMiddleClick;
};

extern float		g_fSecondPerFrame;
extern float		g_fTimer;
extern HWND			g_hWnd;
extern RECT			g_rtClient;
extern POINT		g_MousePos;
extern TInputActionMap  g_InputMap;


static std::wstring mtw(std::string str)
{
	return std::wstring(str.begin(), str.end());
}
static std::string wtm(std::wstring str)
{
	return std::string(str.begin(), str.end());
}
// Singleton
template <class T>
class TSingleton
{
public://TSoundMgr': private 멤버 -> friend
	static T& GetInstance()
	{
		static T theSingleton;
		return theSingleton;
	}	
};

#ifndef SAFE_NEW
#define SAFE_NEW(A,B)  {if(!A) A= new B;}
#endif // !SAFE_NEW

#ifndef SAFE_DEL
#define SAFE_DEL(A)    {if(A) delete A; (A) = 0;}
#endif // !SAFE_DEL


#ifndef SAFE_ZERO
#define SAFE_ZERO(A)    {(A) = 0;}
#endif // !SAFE_DEL


#define TCORE_START void main() {
#define TCORE_RUN 	Sample sample;sample.TRun();
#define TCORE_END }
#define TGAME TCORE_START;TCORE_RUN;TCORE_END;

#define TWINCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow){
#define TWINCORE_RUN 	Sample win;if(win.SetWindow(hInstance)){win.TRun();}
#define TWINCORE_END }
#define TWINGAME TWINCORE_START;TWINCORE_RUN;TWINCORE_END;

