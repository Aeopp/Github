#include <iostream>
#include <string>
#include <memory>
using std::uint32_t;

const int&& foo()
{
	return 1;
};

int main()
{
	auto a = std::make_shared<int32_t>(1);
	auto f = [b = std::move(a)]
	{

	};
};





