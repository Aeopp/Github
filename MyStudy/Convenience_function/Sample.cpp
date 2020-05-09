#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <valarray>
using  namespace  std;

using vector=std::valarray<int32_t> ;

namespace std {
	/*std::valarray<int32_t> operator+
		(std::valarray<int32_t> lhs, std::valarray<int32_t>rhs) {
		std::cout << "qwe";
		return lhs.operator+=(rhs);
	};*/
	int32_t operator*
		(std::valarray<int32_t> lhs, std::valarray<int32_t>rhs) {
		lhs.operator*=(rhs);
		return lhs[0] + lhs[1];
	};
};
int main() {
	std::valarray<int> q{ 1,2,3,4 };
	std::valarray<int> s{ 1,2 };
	auto qwe = s + q;

	int a = 1;
};