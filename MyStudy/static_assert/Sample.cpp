#include <type_traits>
using namespace std;
class Super1{}; 
class Sub1 : public Super1 {}; 

class Super2 {}; 
class Sub2 : public Super2 {}; 

template<typename _Ty>
void process(const _Ty& t)
{
	static_assert(is_base_of<Super1, _Ty>::value
		,"상속관계 "); 
}
    
int main()
{

}

