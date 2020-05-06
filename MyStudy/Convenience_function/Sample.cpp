#include <iostream>
#include <type_traits>
#include <memory>


int main()
{
	
	auto f = [](int* p) {delete p; };

	int* p = new int(2);
	
	auto qwe = std::shared_ptr<int>(p, f);
	
	

	
	
}