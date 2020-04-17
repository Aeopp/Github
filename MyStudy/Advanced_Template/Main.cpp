#include <iostream>
#include <vector> 
using namespace std;
template<typename T,
template<typename E,typename Allocator= std::allocator<E>>                
typename Container = std::vector>
class A
{

};
#include <memory>

int main()
{
	auto Ptr = make_unique<int32_t>(123);
	 
}

