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

class time {
public:
	static inline float_t delta_sec{ 0.f };
	static inline float_t Elapsed_time{ 0.f };
};

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
			// ���ϴ� ������ ����ŭ�� �����ѹ��� ��ȯ
			DisType Dis(Min, Max);
			
			std::vector<decltype(Dis(Generate))> bucket;
			bucket.reserve(N);
			
			std::generate_n(std::back_inserter(bucket), N,[&]() 
			{return Dis(Generate); });
			
			return bucket; 
		};
	};
public :
	
	struct InputMapped
	{
		uint32_t IsAttack;
		uint32_t IsJump;
		uint32_t IsExit;

		uint32_t IsForward;
		uint32_t IsBackward;
		uint32_t IsLeft;
		uint32_t IsRight;

		uint32_t IsLeftClick;
		uint32_t IsRightClick;
		uint32_t IsMiddleClick;
	};
	
	static inline InputMapped InputMaping; 
	static inline HINSTANCE HInstance = nullptr;
	static inline HWND HWnd = nullptr;
	static inline RECT RectClient{};
	static inline random Random{};
	static inline POINT MousePos;

	//  ��ũ�� ��ǥ�� Ŭ���̾�Ʈ ��ǥ�� ��ȯ
	static void inline CursorPosConversion()
	{
		GetCursorPos(&world::MousePos);// ��ũ����ǥ
		ScreenToClient(world::HWnd, &world::MousePos);
	};
};



class  util
{
public:
	template<typename _manager_Type,
		// manager_Interface ��ӹ��� ��ü��� �̱��� �ν��Ͻ� ���� ���
		// �׷��� �ʴٸ� ������ ���� 
		typename = std::is_base_of<manager_Interface<_manager_Type>,
		_manager_Type>::type,
		typename... ParamTypes>
		static _manager_Type& GetInstance(ParamTypes&&... Params) {
		
		static std::unique_ptr<_manager_Type> manager_Ptr = nullptr;
		static std::once_flag Flag;

		// ������ ������ ������� �� �ѹ��� ���ุ �Ѵ�
		std::call_once(Flag, [](auto&&... Params)
			{
				manager_Ptr.reset(new _manager_Type(std::forward<ParamTypes>(Params)...));
			});
		return *manager_Ptr;
	};
	
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

		if (erase_last != _string::npos)
		{
			_filename.erase(erase_first, erase_last + 1);
		}
		return _filename;
	}
}

namespace Debug {
	template<typename MsgTy>
	constexpr auto Log_Impl(const char* __Func, long  __LINE, MsgTy&& Message)
	{
		std::string&& Log = " Function ";
		return Log + __Func + " Line :  " + std::to_string(__LINE) + " \n " + Message;
	};
#define Log(Target) Log_Impl(__FUNCTION__,__LINE__,Target)
};


namespace [[deprecated]] Deprecated
{

	/*static  inline  auto ScreenDC_Deleter(HWND _HWnd)
	{
		return[HWnd = std::move(_HWnd)](HDC _delete) {ReleaseDC(HWnd, _delete); };
	};

	static  constexpr inline  auto _DeleteObject() {
		return 	[](auto _deleter) {DeleteObject(_deleter); };
	};

	template<typename... Params>
	static inline auto _CreateFont(Params&&... params)
	{
		return HFONT(CreateFont(

			std::forward< Params>(params)...), _DeleteObject());
	}

	static inline auto _CreateCompatibleDC(HDC _Hdc, HWND _HWnd)
	{
		return HDC(CreateCompatibleDC(_Hdc), ScreenDC_Deleter(
			std::move(_HWnd)));
	};

	static inline auto _CreateSolidBrush(COLORREF _ColorRef)
	{
		return HBRUSH(CreateSolidBrush(std::move(_ColorRef)),
			_DeleteObject());
	};

	static inline auto _CreateCompatibleBitmap(HDC _Hdc, const LONG right, const LONG bottom)
	{
		return HBITMAP(CreateCompatibleBitmap(_Hdc, right, bottom),
			_DeleteObject(), util::_DeleteObject());
	};

	static inline auto  _GetDC(HWND _HWnd)
	{
		return HDC(GetDC(_HWnd), ScreenDC_Deleter(
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
			return static_cast<HBITMAP>(LoadImage(world::HInstance,
				Name.c_str(),
				IMAGE_BITMAP,
				0, 0,
				LR_DEFAULTSIZE | LR_LOADFROMFILE));
		};
	};*/


	// ����Ʈ�������� ������ (����������)
	// ������ؼ��� L Value �� ĳ�����Ѵ��� �ּҰ��� ���ϰų� �ؾ���
	template<typename Ptr_Ty>
	static constexpr auto Return_DoublePtr(Ptr_Ty& Handle)
	{
		auto ReturnDoublePtr = Handle;
		return &ReturnDoublePtr;
	}

};
