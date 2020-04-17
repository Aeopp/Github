#include <string>
#include <list>
#include <vector> 
#include <algorithm>
#include <initializer_list>
#include <utility>
#include <tuple>
#include <iostream>
#include <iterator>
#include <memory>
#include <chrono>
#include <random>
#include <type_traits>
#include <typeinfo>
#include "List.h"
using namespace std;

template<typename conty, typename =
	decltype(declval<conty>().begin()),
	typename = decltype(declval<conty>().end())>
	void print(const conty& target)
{
	copy(target.begin(), target.end(), ostream_iterator<
		typename conty::value_type>
		(cout, " "));
};
template<typename _T>
void foo(_T good)
{
	typename _T::ty a;
	a = 1234;
	std::cout << a;

	
}
struct A
{
	using ty = int;
};
struct B
{
	static inline string ty = "eqwe";
};
template<typename T>
constexpr void _Typrint(T&& a)
{

};

int main()
{
	int a = 2;
	int& b = a;
	int&& c = int();

	_Typrint(a);
	_Typrint(b);
	_Typrint(c);
}