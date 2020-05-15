#include <memory>
#include <iostream>
using namespace std;
#include <vector>activation.h
template<typename t,template<typename>typename  v>
auto foo() {
	return v<t>{};
}



int main() {
	auto  qwe = foo<int, std::vector>();

}