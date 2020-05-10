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

class World {
public:
	static inline std::weak_ptr<HINSTANCE__> InstanceHandle;
	static inline std::weak_ptr<HWND__> WindowHandle;;
	static inline RECT ClientRect; 
	static inline float_t FramePerSecond = 0.f;
	static inline float_t Timer = 0.f; 
	static inline POINT MousePosition;
	static inline InputActionMap InputMapState;
};

// GetDC로 얻은 핸들을 반환하는 형식
static inline auto HDCReleaseDC = [](HDC DisplayHandle) {
	if (auto SharedWindowHandle = World::WindowHandle.lock();
		SharedWindowHandle)
	{
		ReleaseDC(SharedWindowHandle.get(), DisplayHandle);
	}
};
// CreateCompatibleDC로 얻은 핸들을 반환하는 형식
static inline auto HDCDeleteDC = [](HDC DisplayHandle) {
	DeleteDC(DisplayHandle);
};
static inline auto BitmapHandleDeleter = [](HBITMAP BitmapHandle) {
	DeleteObject(BitmapHandle);
};
static  inline auto ObjectDeleter = []<typename HandleTypeCheck, typename =
	std::is_invocable<decltype(DeleteObject), HandleTypeCheck>>(HandleTypeCheck Handle) {
	DeleteObject(Handle);
};


static std::wstring mtw(std::string str)
{
	return std::wstring(str.begin(), str.end());
}
static std::string wtm(std::wstring str)
{
	return std::string(str.begin(), str.end());
}

#define DEFAULT_MOVE_COPY(Target)       \
public:\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

// Singleton
// Don't Copy Don't Move
#define DELETE_MOVE_COPY(Manager)   \
public:\
Manager(Manager&&)noexcept = delete;\
Manager& operator=(Manager&&)noexcept = delete;\
Manager(const Manager&) = delete;\
Manager& operator=(const Manager&) = delete;\

template <class ManagerType>
class SingleTon
{
public:
	// TODO :: Sub 클래스 Super 클래스 프렌드 지정해줘야함
	// TODO :: 생성자 상속 사용하면 안됨
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
protected:
	SingleTon() = default;
private:
	~SingleTon()noexcept = default;
	DELETE_MOVE_COPY(SingleTon)
};

#define TCORE_START void main() {
#define TCORE_RUN 	Sample sample;sample.TRun();
#define TCORE_END }
#define TGAME TCORE_START;TCORE_RUN;TCORE_END;

#define TWINCORE_START int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPWSTR lpCmdLine,int nCmdShow){
#define TWINCORE_RUN 	Sample win;if(win.SetWindow(hInstance)){win.TRun();}
#define TWINCORE_END }
#define TWINGAME TWINCORE_START;TWINCORE_RUN;TWINCORE_END;

