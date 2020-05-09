#pragma once
#include <memory>
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
#include <mutex>
using namespace std;
using  tstring = basic_string<TCHAR> ;

typedef basic_string<char>  C_STR;
typedef basic_string<wchar_t> W_STR;
typedef std::vector<tstring> T_STR_VECTOR;

//추가종속성 winmm.lib; fmod_vc.lib; TCoreLib.lib;
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "fmod_vc.lib")

enum class EKeyState : uint8_t { Free = 0, Push, Hold, Up };

namespace Utility {
	template<typename StringType>
	constexpr StringType inline PathDelete(const StringType& FullPath)
	{
		StringType Filename = FullPath;

		auto erase_first = Filename.find_first_of('.');
		auto erase_last = Filename.find_last_of('/');

		if (erase_last != StringType::npos)
		{
			Filename.erase(erase_first, erase_last + 1);
		}
		return Filename;
	}
};
namespace Debug {
	// string 만 사용 가능
	static auto LogImplementation(const char* __Func, long  __LINE,std::string Message)
	{
		std::string Log = " Function ";
		return (Log + __Func + " Line :  " + std::to_string(__LINE) + " \n " + Message).c_str();
	};
#define Log(Target) LogImplementation(__FUNCTION__,__LINE__,Target)
};
class World {
public:
	static inline HINSTANCE InstanceHandle = nullptr;
	static inline HWND WindowHandle = nullptr;
	static inline RECT ClientRect; 
	static inline float_t FramePerSecond = 0.f;
	static inline float_t Timer = 0.f; 
};
struct InputActionMap
{
	EKeyState Attack;
	EKeyState Jump;
	EKeyState Exit;

	EKeyState WKey;
	EKeyState SKey;
	EKeyState AKey;
	EKeyState DKey;

	EKeyState LeftClick;
	EKeyState RightClick;
	EKeyState MiddleClick;
};

extern float		g_fTimer;
extern POINT		g_MousePos;
extern InputActionMap  g_InputMap;


static std::wstring mtw(std::string str)
{
	return std::wstring(str.begin(), str.end());
}
static std::string wtm(std::wstring str)
{
	return std::string(str.begin(), str.end());
}
// Singleton
template <class ManagerType>
class SingleTon
{
public:
	// TODO :: Sub 클래스 Super 클래스 프렌드 지정해줘야함
	template<typename...Types>
	static ManagerType& Instance(Types&&... params)
	{
		static std::unique_ptr<ManagerType> InstancePtr;
		static std::once_flag OnceFlag;
		std::call_once(OnceFlag,[](auto&&... params){
			InstancePtr.reset(new ManagerType(std::forward<Types>(params)...)); },
			std::forward<Types>(params)...);
		return *(InstancePtr.get());
	};
public :
	SingleTon(SingleTon&&)noexcept=delete;
	SingleTon& operator=(SingleTon&&)noexcept = delete;
	SingleTon(const SingleTon&)=delete;
	SingleTon& operator=(const SingleTon&)=delete;
protected:
	SingleTon() = default;
private:
	~SingleTon()noexcept = default;
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

