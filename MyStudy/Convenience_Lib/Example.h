#pragma once
#include "Convenience_function.h"


namespace Example
{
	constexpr auto concatExample()
	{
		auto twice([](int i) {return i * 2; });
		auto thrice([](int i) {return i * 3; });

		// twice(thrice(plus(2,3) ) ) 로 평가될것
		return  [&]()
		{
			auto combined(util::concat(twice, thrice, std::plus<int>{}));
			std::cout << combined(2, 3);
		};
	};
	
	constexpr auto multicall_foreach_Example()
	{
		auto brace_print = [](char a, char b)
		{
			return [=](auto x) {std::cout << a << x << b << ", "; };
		};

		auto f{ brace_print('(', ')') };
		auto g{ brace_print('[', ']') };
		auto h{ brace_print('{', '}') };

		auto nl{ [](auto) {std::cout << '\n'; } };

		auto call_fgh{ util::multicall(f,g,h,nl) };
		util::for_each(call_fgh, 1, 2, 3, 4, 5);
	};

	constexpr auto Map_Reduce_Example ()
	{
		// transform_if
		
		std::istream_iterator<int> it{ std::cin };
		std::istream_iterator<int> end_it;

		auto even{ [](int i) {return i % 2 == 0; } };
		auto twice{ [](int i) {return i * 2;  } };
		

		std::accumulate(it, end_it,
			std::ostream_iterator<int>{std::cout, ","},
			util::filter(even)
			(util::Map(twice)(util::copy_and_advance() )  )  );
	}

	auto multiinterface_Example()
	{
		auto Fn1 = [](int a) {std::cout << __FUNCTION__ << std::endl; };
		auto Fn2 = [](float a) {std::cout << __FUNCTION__ << std::endl; };
		auto Fn3 = [](int* a) {std::cout << __FUNCTION__ << std::endl; };

		util::multiinterface Tester{ std::move(Fn1), std::move(Fn2),std::move(Fn3) };

		Tester(77l);
		Tester(99.999f);
		Tester(nullptr);
	}
}

