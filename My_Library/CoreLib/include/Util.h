#pragma once
#include <utility>
#include <string>
#include <memory>
#include <stdexcept>
#include <mutex>
#include "manager_Interface.h"

class time {
public:
	static inline float_t delta_sec{ 0.f };
	static inline float_t Elapsed_time{ 0.f };
};

namespace Debug
{
	template<typename MsgTy>
	constexpr auto Log_Impl(const char* __Func, long  __LINE, MsgTy&& Message)
	{
		std::string&& Log = " Function ";
		return Log + __Func + " Line :  " + std::to_string(__LINE) + " \n " + Message;
	};
#define Log(Target) Log_Impl(__FUNCTION__,__LINE__,Target)
}


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
		return *manager_Ptr.get();
	};
};