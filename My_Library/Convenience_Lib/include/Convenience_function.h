#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <iterator>
#include <numeric>
// 사용방법 Sample.cpp 올려놨음

namespace util
{
	// 클라이언트가 F,G,H 함수를 제공하면
// F(G(H(Params...))) 로 평가.
// 아래함수와 똑같을 것이다.
//// /*template<typename F,typename G,typename H>
//auto concat(F f, G g, H h)
//{
//	return [=](auto... params)
//	{
//		return f(g(h(params...)));
//	};
//}*/
	template<typename _Ty, typename ...Tys>
	constexpr auto concat(_Ty&& T, Tys&&... Ts)
	{
		if constexpr (sizeof...(Ts) > 0)
		{
			return [&](auto&&... Params)
			{
				return  T(concat(std::forward<decltype(Ts)>(Ts)...)(std::forward<decltype(Params)>(Params)...));
			};
		}
		else
		{
			return T;
		}
	};
	template<typename... _Tys>
	constexpr auto multicall(_Tys&&... functions)
	{
		return [&](auto&& Param)
		{
			//  std::initializer_list<int>{functions(Param)};
			//  위 표현식처럼 해도됨
			
			// 초기화 리스트는 매번 functions(Param) 를 호출한다.
			// 펑션의 리턴값이 필요하지 않은 상황이기 때문에
			// 실제 초기화 리스트의 초기화는 0 으로 초기화함
			// 그렇기 위해서는 함수의 반환값을 void 로 무효화시켜야함
			// functions(Param)... 를 ((functions(Param),0)... 으로 감싸넣어서
			// 0을 초기화 목록에 넣어 반환값을 버린다
			// 또한 void로 형변환하면 반환값을 실제로 처리하지 않는다.
			 return(void)std::initializer_list<int>{
				((void)functions(Param), 0)...
			};
		};
	};

	template<typename FTy, typename... Tys>
	constexpr  auto for_each(FTy&& Function, Tys&&... Params)
	{
		(void)std::initializer_list<int>{
			((void)Function(Params), 0)...
		};
	}
	// 좌항 함수 우항 함수의 Param 의 논리반환식을
	// 논리합으로 만들어줌
	template<typename Bi_func, typename LhsTy, typename RhsTy>
	constexpr  auto combine(Bi_func& Bi_Func, LhsTy& LhsFunc, RhsTy& RhsFunc)
	{
		return [&](auto& param)
		{
			return Bi_Func(LhsFunc(param), RhsFunc(param));
		};
	}

	template<typename _Ty>
	auto Map(_Ty&& Func)
	{
		return [&](auto&& reduce_fn)
		{
			return [&](auto&& accum, auto&& input)
			{
				return reduce_fn(accum, Func(input));
			};
		};
	};
	// Pred true 표현식일 경우
	// 값을 계속 누적한다
	// false 표현식일경우 중지한다.
	template<typename _Ty>
	auto filter(_Ty&& predicate)
	{
		return [&](auto&& reduce_fn)
		{
			return [&](auto&& accum,auto&& input)
			{
				if(predicate(input))
				{
					return reduce_fn(accum, input); 
				}else
				{
					return accum; 
				}
			};
		};
	}

	
	template<typename ...Tys>
	class multiinterface : public Tys...{
	public:
		// using Types... function ... 파라미터 언팩
		// 상속받은 클래스의 함수를 사용할수 있게 해준다
		using Tys::operator()...;

		// 람다를 받고싶다면 반드시 r-value 로 받아야한다
		// 임시객체로 받거나 move 로 받아야한다.

		// 1번 방법 생성자 만들어주기
		multiinterface(Tys&&... Params) : Tys(Params)... {};
	};
	// 2번 방법 후행반환형식 지정
	template<typename ...Tys>
	multiinterface(Tys&&...)->multiinterface<Tys...>;

	
	
	
	// 싱글턴을 하고싶다면 상속받아야하는 구조체
	// 타입속성 더미 구조체로 해도 상관 없을듯
	// 상속 안하고자 할때도
	// 싱글턴 인터페이스 짤때마다 긁어다 써도 좋을듯
	template<typename ManagementType>
	struct ManagerInterface/*manager_traits*/ {
	protected:
		ManagerInterface() = default;
		virtual ~ManagerInterface() noexcept(true) = default;
	public:
		// my manager Type
		using Type = ManagementType;
		using Super = ManagerInterface<ManagementType>;
		
		friend class std::unique_ptr<ManagerInterface>;
		friend struct std::unique_ptr<ManagerInterface>::deleter_type;
		
		//ManagerInterface(ManagerInterface&&) = delete;
		//ManagerInterface&operator=(ManagerInterface&&) = delete;
		//ManagerInterface(const ManagerInterface&) = delete;
		//ManagerInterface&operator=(const ManagerInterface&) = delete;
	};
	template<typename ManagerType,
		// manager_Interface 상속받은 객체라면 싱글톤 인스턴스 생성 허용
		// 그렇지 않다면 컴파일 에러 
		typename = std::is_base_of<ManagerInterface<ManagerType>,
		ManagerType>::type,
		typename... ParamTypes>
		static ManagerType& GetInstance(ParamTypes&&... Params) {

		static std::unique_ptr<ManagerType> manager_Ptr = nullptr;
		static std::once_flag Flag;

		// 스레드 개수와 상관없이 단 한번의 실행만 한다
		std::call_once(Flag, [](auto&&... Params)
			{
				manager_Ptr.reset(new ManagerType(std::forward<ParamTypes>(Params)...));
			});
		return *manager_Ptr.get();
	};
};

namespace Call
{
	template<typename _Separator, typename ...Args>
	constexpr  void printer(_Separator&& Separator, Args&&... args) {
		(std::cout << ... << std::forward<Args>(args)) << std::forward<_Separator>(Separator);
	};
	template<typename Callable_Ty, typename ...Tys>
	constexpr  void Params(const Callable_Ty& Callable, Tys&&... Params)
	{
		(std::invoke(std::forward<decltype(Callable)>(Callable),
		std::forward<decltype(Params)>(Params)), ...);
	}
	template<typename Ty, typename ...Callable_Tys>
	constexpr  void Callables(const Ty& Param, Callable_Tys&& ... Callables)
	{
		(std::invoke(std::forward<decltype(Callables)>(Callables),
			std::forward<decltype(Param)>(Param)), ...);
	}
	
	template<typename Init,typename... Tys>
	constexpr auto Init_diff(Init&& Start, Tys&&... Params)
	{
		return (Start - ... - Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Sum(Init&& Start, Tys&&... Params)
	{
		return (Start + ...  + Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Multiply(Init&& Start, Tys&&... Params)
	{
		return (Start * ... * Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Division(Init&& Start, Tys&&... Params)
	{
		return (Start * ... * Params);
	};
	template<typename Init, typename... Tys>
	constexpr auto Init_Average(Init&& Start, Tys&&... Params)
	{
		return ((Start * ... * Params) / (sizeof...(Params) + 1));
	};
}

namespace Debug
{
	template<typename MsgTy>
	constexpr auto Log_Impl(const char* __Func,long  __LINE,MsgTy&& Message)
	{
		std::string&& Log = " Function ";
		return Log + __Func + " Line :  " + std::to_string(__LINE) +" \n " + Message;
	};
	
	#define Log(Target) Log_Impl(__FUNCTION__,__LINE__,Target)
}