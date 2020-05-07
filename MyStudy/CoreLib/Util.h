#pragma once
#include <utility>
#include <string>
#include <memory>
#include <stdexcept>
#include <mutex>
#include "manager_Interface.h"
#include <Windows.h>
#include <type_traits>
#include <random>
#include "Type_Aliases.h"
#include <fmod.hpp>
#include <map>


//인풋 로직 표현
struct InputAction{

};

class time {
public:
	static inline float_t delta_sec{ 0.f };
	static inline float_t Elapsed_time{ 0.f };
};

//namespace Debug
//{
//	template<typename MsgTy>
//	constexpr auto Log_Impl(const char* __Func, long  __LINE, MsgTy&& Message)
//	{
//		std::string&& Log = " Function ";
//		
//		return Log + __Func + " Line :  " + std::to_string(__LINE) + " \n " + Message;
//	};
//#define Log(Target) Log_Impl(__FUNCTION__,__LINE__,Target)
//}

class world
{
private:
	class random
	{
	public:
		using DisType= std::uniform_int_distribution<>;
	private:
		std::random_device Random_Device;
		std::mt19937 Generate;
	public:
		explicit random()noexcept
			:Random_Device{}, Generate{ Random_Device() }   {};
		
		template<typename number_type>
		inline auto Get(const number_type Min,const number_type Max,
			const uint32_t N)
		{
			// 원하는 구간과 수만큼의 랜덤넘버를 반환
			DisType Dis(Min, Max);
			
			std::vector<decltype(Dis(Generate))> bucket;
			bucket.reserve(N);
			
			std::generate_n(std::back_inserter(bucket), N,[&]() 
			{return Dis(Generate); });
			
			return bucket; 
		};
	};
public :
	static inline HINSTANCE_ptr HInstance = nullptr;
	static inline HWND_ptr HWnd = nullptr;
	static inline RECT RectClient{};
	static inline random Random{};
	static inline POINT MousePos;

	//  스크린 좌표를 클라이언트 좌표로 변환
	static void inline CursorPosConversion()
	{
		GetCursorPos(&world::MousePos);// 스크린좌표
		ScreenToClient(world::HWnd.get(), &world::MousePos);
	};
};



class  util
{
public:
	template<typename _manager_Type,
		// manager_Interface 상속받은 객체라면 싱글톤 인스턴스 생성 허용
		// 그렇지 않다면 컴파일 에러 
		typename = std::is_base_of<manager_Interface<_manager_Type>,
		_manager_Type>::type,
		typename... ParamTypes>
		static _manager_Type& GetInstance(ParamTypes&&... Params) {
		
		static std::unique_ptr<_manager_Type> manager_Ptr = nullptr;
		static std::once_flag Flag;

		// 스레드 개수와 상관없이 단 한번의 실행만 한다
		std::call_once(Flag, [](auto&&... Params)
			{
				manager_Ptr.reset(new _manager_Type(std::forward<ParamTypes>(Params)...));
			});
		return *manager_Ptr.get();
	};
	
	static  inline  auto ScreenDC_Deleter(HWND_ptr _HWnd)
	{
		return [HWnd = std::move(_HWnd)](HDC _delete) {ReleaseDC(HWnd.get(), _delete); };
	};

	static  constexpr inline  auto _DeleteObject() {
	return 	[](auto _deleter) {DeleteObject(_deleter); };
	};
	
	template<typename... Params>
	static inline auto _CreateFont(Params&&... params)
	{
		return HFONT_ptr(CreateFont(

			std::forward< Params>(params)...), _DeleteObject());
	}
	
	static inline auto _CreateCompatibleDC(HDC_ptr _Hdc, HWND_ptr _HWnd)
	{
		return HDC_ptr(CreateCompatibleDC(_Hdc.get()), ScreenDC_Deleter(
			std::move(_HWnd)));
	};

	static inline auto _CreateSolidBrush(COLORREF _ColorRef)
	{
		return HBRUSH_ptr(CreateSolidBrush(std::move(_ColorRef)),
			_DeleteObject());
	};
	
	static inline auto _CreateCompatibleBitmap(HDC_ptr _Hdc,const LONG right, const LONG bottom)
	{
		return HBITMAP_ptr( CreateCompatibleBitmap(_Hdc.get(), right, bottom),
			_DeleteObject() ,util::_DeleteObject());
	};
	
	static inline auto  _GetDC(HWND_ptr _HWnd)
	{
		return HDC_ptr(GetDC(_HWnd.get()), ScreenDC_Deleter(
		std::move(_HWnd)));
	}
	
	static  constexpr inline  auto FModSystem_Release()
	{
		return [](FMOD::System* _delete) {
			_delete->close();
			_delete->release();
		};
	};
	
	static   inline  auto LoadImage_To_BitMap(const std::wstring& Name)
	{
		return  [Name]()->HBITMAP
		{
			return static_cast<HBITMAP>(LoadImage(world::HInstance.get(),
				Name.c_str(),
				IMAGE_BITMAP,
				0, 0,
				LR_DEFAULTSIZE | LR_LOADFROMFILE));
		};
	};

	// 스마트포인터의 포인터 (더블포인터)
	// 얻기위해서는 L Value 로 캐스팅한다음 주소값을 구하거나 해야함
	template<typename Ptr_Ty>
	static constexpr auto Return_DoublePtr(Ptr_Ty& Handle)
	{
		auto ReturnDoublePtr = Handle.get();
		return &ReturnDoublePtr;
	}

	template<typename Key>
	static constexpr inline bool EquivalenceCompare(const Key& Lhs, const Key& Rhs)
	{
		return (!(Lhs < Rhs)) && (!(Rhs < Lhs));
	};
};

namespace File
{
	template<typename _string>
	constexpr auto inline PathDelete(const _string& filename)
	{
		_string _filename = filename;
		
		auto erase_first = _filename.find_first_of('.');
		auto erase_last = _filename.find_last_of('/');
	
		if(erase_last != _string::npos)
		{
			_filename.erase(erase_first, erase_last+1);
		}
		return _filename; 
	}
}