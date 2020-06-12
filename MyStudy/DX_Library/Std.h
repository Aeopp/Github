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

// �ΰ˻�
template<typename _ptrType>
bool constexpr IsValid(_ptrType ptr) {
	
	static_assert((std::is_pointer_v < _ptrType > == true 
		|| std::is_same_v<std::shared_ptr<_ptrType>::element_type, _ptrType> )
		&& L"is not pointer type");
	
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

//�߰����Ӽ� winmm.lib; fmod_vc.lib; TCoreLib.lib;
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

//extern float		g_fSecondPerFrame;
//extern float		g_fTimer;
//extern HINSTANCE	g_hInstance;
//extern HWND			g_hWnd;
//extern RECT			g_rtClient;
//extern POINT		g_MousePos;

//// Singleton
//template <class T>
//class Singleton
//{
//public://TSoundMgr': private ��� -> friend
//	static T& GetInstance()
//	{
//		static T theSingleton;
//		return theSingleton;
//	}
//};

// ����� ����Ǵ� CPP�� �Ҹ��� ������ �ݵ�ñ���
#define DECLARE_SINGLETON(Target)        \
private:\
friend class std::unique_ptr<Target>::deleter_type;      \
friend class std::unique_ptr<Target>;         \
friend class SingleTon<Target>;\
Target();\
virtual ~Target()noexcept;       \

#define DECLARE_DEFAULT_MOVE_COPY(Target)       \
public:\
Target(Target&&)noexcept = default;\
Target& operator=(Target&&)noexcept = default;\
Target(const Target&) = default;\
Target& operator=(const Target&) = default;\

// Singleton
// �̵� ī�� ���� 
#define DECLARE_DELETE_MOVE_COPY(Manager)   \
public:\
Manager(Manager&&)noexcept = delete;\
Manager& operator=(Manager&&)noexcept = delete;\
Manager(const Manager&) = delete;\
Manager& operator=(const Manager&) = delete;\

#include <memory>
#include <type_traits>
#include <mutex>
// TODO :: Sub Ŭ���� Super Ŭ���� ������ �����������
// TODO :: ������ ��� ����ϸ� �ȵ�
// TODO :: private �⺻ ������ �Ҹ��� �����ϰ� �ݵ�� cpp�� ����
// TODO :: SINGLETON_DECLARE(SubClass) DELETE_MOVE_COPY(Subclass) 
// TODO :: friend class std::unique_ptr<SubClass>::deleter_type;
template <class ManagerType>
class SingleTon
{
public:
	template<typename...Types>
	static ManagerType& Instance(Types&&... params)
	{
		static std::unique_ptr<ManagerType> InstancePtr;
		static std::once_flag OnceFlag;
		std::call_once(OnceFlag, [](auto&&... params) {
			InstancePtr.reset(new ManagerType(std::forward<Types>(params)...)); },
			std::forward<Types>(params)...);
		return *(InstancePtr.get());
	};
protected:
	SingleTon() = default;
	~SingleTon()noexcept = default;
private:
	DECLARE_DELETE_MOVE_COPY(SingleTon)
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
