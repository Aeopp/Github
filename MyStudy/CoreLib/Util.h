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
//
//using HINSTANCE_ptr		= std::shared_ptr<std::remove_pointer_t<HINSTANCE>>;
//using HWND_ptr			= std::shared_ptr<std::remove_pointer_t<HWND>>;
//using HBITMAP_ptr		= std::shared_ptr<std::remove_pointer_t<HBITMAP>>;
//using HDC_ptr			= std::shared_ptr<std::remove_pointer_t<HDC>>;
using HINSTANCE_ptr = std::shared_ptr<HINSTANCE__>;
using HWND_ptr = std::shared_ptr<HWND__>;
using HBITMAP_ptr = std::shared_ptr<HBITMAP__>;
using HDC_ptr = std::shared_ptr<HDC__>;

인풋 로직 표현
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
		return [&_HWnd](HDC _delete) {ReleaseDC(_HWnd.get(), _delete); };
	};
	
	static  constexpr inline  auto Bitmap_Deleter() {
	return 	[](HBITMAP _deleter) {DeleteObject(_deleter); };
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
};