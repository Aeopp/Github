#include <iostream>
#include <functional>

using namespace std;
template<class Arg, class Ret>
class FPtr
{
public:
	using FunType = 
	template<class Arg, class Ret>
	std::function<Ret(const Arg& A, const int32_t i)>;

	FunType fptr;

	FPtr(FunType&& set)
	{
		fptr = set;
	};

	Ret operator(const Arg& A,const int32_t i) 
	{return fptr(A, i);};
};


int main()
{

}