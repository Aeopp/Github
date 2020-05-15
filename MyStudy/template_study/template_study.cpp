#include <iostream>
#include <thread>
#include <deque>
#include <list>
#include <vector>
#include<functional>
#include <iterator>
#include <algorithm>

static bool begins_with_a(const std::string& s)
{
	return s.find("a") == 0;
};
static bool ends_with_b(const std::string& s)
{
	return s.rfind("b") == s.length() - 1;
};
template<typename A,typename B,typename F>
auto combine(F binary_func, A a, B b)
{
	return [=](auto param)
	{
		return binary_func(a(param), b(param));
	};
};

template<typename _Ty,
	typename = _Ty::iterator>
static auto consumer(_Ty&container)
{
	return [&](auto value)
	{
		container.push_back(value);
	}; 
}
template<typename _Ty>
static void print(const _Ty& c)
{
	for(auto i: c)
	{
		std::cout << i << " , ";
	}
	std::cout << '\n'; 
}
//template<typename T,typename...Ts>
//auto concat(T t, Ts...ts)
//{
//	// 남은 파라미터가 1개 이상 이라면
//	if constexpr (sizeof...(ts) > 0)
//	{
//		return [=](auto...parameters)
//		{
//			return t(concat(ts...)(parameters...));
//		};
//	}
//	else
//	{
//		return t;
//	}
//};

template<typename T,typename ...Ts>
auto concat(T t,Ts...ts)
{
	if constexpr (sizeof...(ts) > 0)
	{
		return [=](auto...parameters)
		{
			return t(concat(ts...)(parameters...));
		};
	}else
	{
		return [=](auto...parameters)
		{
			return t(parameters...);
		}; 
	}
}
template<typename F,typename G,typename H>
auto concat(F f,G g,H h)
{
	return [=](auto...params)
	{
		return f (   g ( h (params...) ) );
	}; 
}
//template<typename ... f>
//static auto multicall(f...functions)
//{
//	return [=](auto x)
//	{
//		return std::initializer_list<int>{
//			(void)functions(x)...
//		};
//	}; 
//}



using namespace std;

template<typename f,typename p,typename ... fs>
static auto for_each (f F,p x,fs... xs)
{
	if constexpr(sizeof...(fs)>0)
	{
		F(x);
		for_each(F, xs...);
	}
	else
	{
		for_each(F, xs...);
	}
}
// 제한된 파라미터에 여러개의 펑션을 대리호출해줌
// 파라미터는 고정되어있으나 펑션 여러개를 한꺼번에
//  깔끔하게 호출하고 싶다면 사용하면됨
//  
template<typename... Funcs ,typename _Ty>
void foo(_Ty param , Funcs... funcs)
{
	(void)std::initializer_list<int32_t>{
		((void)funcs(param),0)                  ...
	}; 
}
template<typename... _Ty, typename Funcs>
void foo2(Funcs param, _Ty... funcs)
{
	(void)std::initializer_list<int32_t>{
		((void)param(funcs), 0)                  ...
	};
};
auto barfac()
{
	return [](auto i)
	{
		std::cout << i << std::endl;
		return 1;
	};
}
// 여러개의 함수를 하나로 합쳐주는 헬퍼함수
// ex   Funcs : A B C   params  1,2,3;
//  A( B( C(1,2,3) ) );
template<typename helper,typename ... funcs>
auto func_concat(helper _func, funcs... _funcs)
{
	if constexpr(sizeof...(_funcs)>0)
	{
		
		auto functor__ = [&](auto ... params)
		{
			auto functor = func_concat(_funcs...);
			functor(params...); 
		};
		
		return functor__; 
	}else
	{
		 auto functor_____ = [&](auto...params)
		{
			 _func(params...); 
		};

		 return functor_____; 
	}
}
int main()
{
	
	auto bar_bar = [](auto a,auto b,auto c)
	{
		std::cout << a << " " << b << " " << c << std::endl;
		return a + b + c; 
	};
	auto tester = func_concat(bar_bar, bar_bar, bar_bar, bar_bar);
	
	tester("poi"s,"wqe"s,"abc"s);
	
	//foo(1,bar,bar,bar,bar,bar);
	
	//std::deque<int> d;
	//std::list<int> l;
	//std::vector<int> v;

	//const std::vector<std::function<void(int)>> consumers
	//{ consumer(d),consumer(l),consumer(v) };
	//consumers[0](123);

	//for (size_t i{ 0 }; i < 10; ++i)
	//{
	//	for (auto&& consume : consumers)
	//	{
	//		consume(i);
	//	}
	//};

	//print(d);
	//print(l);
	//print(v);


	//auto twice{ [](int i) { return i * 2; } };
	//auto thrice([](int i) {return i * 3; });

	//auto combined{concat(twice,thrice,std::plus<int>{} )}; 
	//std::cout << combined(2, 3);

	//auto a_xxx_b(combine(std::logical_and<bool>{}, begins_with_a,
	//	ends_with_b));

	//std::copy_if(std::istream_iterator<std::string>{std::cin}, {},
	//	std::ostream_iterator<std::string>(std::cout, " "),
	//	a_xxx_b);

	////auto f(       brace_print('(', ')')          );
	////auto g(brace_print('(', ')'));
	////auto h(brace_print('(', ')'));
	////auto nl = [](auto) {std::cout << '\n';  };
	////
	////auto call_fgh(multicall(f, g, h, nl));
	////for_each(call_fgh, 1, 2, 3, 4, 5);


	
	
	
};