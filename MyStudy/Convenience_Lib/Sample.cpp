#include "Convenience_function.h"
#include <memory>

template<typename value_type, typename delete_type, template<typename> typename 
ptr_type>
auto foo()
{
	return ptr_type<value_type, delete_type>(new value_type, delete_type{});
};
auto var = [](auto) {};
int main()
{
	auto wer = foo<int, decltype(var), std::unique_ptr>();

	
	
}