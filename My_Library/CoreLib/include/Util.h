#pragma once
#include <utility>
#include <string>
#include <memory>
#include <stdexcept>
#include <mutex>
#include "manager_Interface.h"

#define DEBUG

#ifdef DEBUG 
#define Log(x) (__FUNCTION__##x)
#endif

// TODO :: __FUNCTION__ 이 제대로 작동할 법한 방법이 없어서 매크로 사용  
namespace debug {
	template<typename _Msg_Ty>
	constexpr auto log(_Msg_Ty msg) {
		return (std::move(msg) + __FUNCTION__ + __LINE__);
	};
	// debug Helper 
}

class time {
public:
	static inline float_t delta_sec{0.f};
	static inline float_t Elapsed_time{0.f};
};

class  util
{
public : 

	template<typename _manager_Type,typename... ParamTypes>
	static _manager_Type& GetInstance(ParamTypes&&... Params) {
		// 매니저 인터페이스를 상속받은 객체라면 싱글톤 인스턴스 생성 허용
		// 그렇지 않다면 예외를 전파
		if constexpr (std::is_base_of_v<manager_Interface<_manager_Type>,
			_manager_Type>) {
			static std::unique_ptr<_manager_Type> manager_Ptr = nullptr;
			static std::once_flag Flag;

			// 스레드 개수와 상관없이 단 한번의 실행이 보장됨 
			std::call_once(Flag, []	(auto&&... Params)
				{
					manager_Ptr.reset(new _manager_Type(std::forward<ParamTypes>(Params)...));
				});
			
			return *manager_Ptr.get();
		}
		else
			throw std::invalid_argument(__FUNCTION__"Invalid template Type Param");
	};
};