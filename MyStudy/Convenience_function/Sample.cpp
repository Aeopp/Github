#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <valarray>
#include <type_traits>
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
void foo(int,float) {};
int main() {
	std::cout << std::is_invocable_v<decltype(foo), int,std::string>;
};