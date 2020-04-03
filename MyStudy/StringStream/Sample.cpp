#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

class MyStringBuffer : public stringbuf
{
public:
	uint8_t &operator[](size_t index)
	{
		uint8_t *b = (uint8_t*)pbase();
		return b[index];
	};
	size_t size()
	{
		return pptr() - pbase(); 
	};
};
struct dHeader
{
	uint32_t len;
	uint32_t type;
	uint32_t bodyNum;
};
typedef struct 
{
	dHeader ph;
	char msg[1024];
}UPCAKET, *P_UPACKET;
constexpr int PACKET_HEADER_SIZE = 12;
std::ostream& operator<<(std::ostream& out, dHeader& h)
{
	out.write(reinterpret_cast<char*>(&h), sizeof(dHeader));
	return out; 
}

//std::istream& operator>> (std::istream& in, dHeader& h)
//{
//	dHeader values;
//	 // in.read(reinterpret_cast<char*> (&values),sizeof())
//};



void f1()
{
	cout << "1";
};
void f2()
{
	cout << "2";
};
void f3()
{
	cout << "3";
};

using q = void(*);
void(*a);
void(*b);
void(*c);
void call(q p1, q p2, q p3)
{
	return; 
}
int main()
{
	a = f1;
	b = f2;
	c = f3;
	call(a, b, c);
	call(a, b, c); 
	call(a, b, c); 
	call(a, b, c); 
	call(a, b, c);
	call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c); call(a, b, c);
};

