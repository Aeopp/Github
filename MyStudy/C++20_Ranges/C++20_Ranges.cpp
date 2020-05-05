#include <iostream>
#include <vector>
#include <optional>
#include <valarray>
#include <list>
#include <map>
int main()
{
	constexpr auto cartesian{ [=](auto ...xs) constexpr {
		return [=](auto f) constexpr
		{
			(void)std::initializer_list<int>{
				((void)call_cart(f, xs, xs...), 0)...
			};
		};
	}
	};

	auto call_cart{ [](auto f, auto x, auto...rest) constexpr {
		(void)std::initializer_list<int>{
			((     (x < rest)  ? (void)f(x,rest) : (void)0),0)...
		};
		} };

	std::map<int, float> q;
	
}
