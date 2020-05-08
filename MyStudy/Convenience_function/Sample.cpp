#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
using  namespace  std;

class A
{
public :
	A() = default;
	virtual ~A() = default;
	A& operator=(A&&) = default;
	A& operator=(const A&) = default;
	A(const A&) = default;
	A(A&&) = default;
protected:

private:
	void foo() {};
};

class B : public A
{
	using A::A;
	B(int a) {};
};
int main()
{
	B b;
	b;
	b = B{};
	
};


