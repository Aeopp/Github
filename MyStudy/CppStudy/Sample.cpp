#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <xutility>
#include <iterator>
#include <string>
#include <random>
#include <chrono>
#include <stack>
#include <set>
#include <map>
#include <list>
#include <memory>
using namespace std;
//struct A
//{
//	friend void operator<<(ostream& Out, const A& t)
//	{
//		Out << "Iteratable    ";
//	};
//};
struct ab
{
	int a; 
	ab(int i) : a{ i } {};
};
using namespace std; 

//template<typename T,
//typename std::enable_if_t<std::is_same_v<T,ab>>* = nullptr>
//ostream& operator<<(ostream& out, T& target)
//{
//		if constexpr (std::is_pointer_v<T>)
//			out << target->a;
//		else
//		{
//			out << target.a;
//
//			if constexpr (std::is_pointer_v<T>)
//			{
//				// ???? 
//				target->a;
//				using qwe = typename T::qwe;
//				qwe asd;
//				std::vector<qwe> asd;
//				asd.resize(100);
//				// ???????
//			}
//		};
//		return out;
//};

#include <queue>
int main()
{
	/*std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int32_t> dis(0, 100);
	std::_Erase_nodes_if
	std::vector<int> arr;
	arr.reserve(100);
	auto back_inserter = std::back_inserter(arr);
	std::generate_n(back_inserter, 100, [&dis, &mt] {return dis(mt); });
	auto sevenfive = 0.77f * arr.size(); 
	std::nth_element(std::begin(arr), std::begin(arr) + sevenfive, std::end(arr));
	std::cout << *(std::begin(arr) + sevenfive);

	partition(begin(arr), end(arr), [](auto& e) {return e % 2;  });

	copy(begin(arr), end(arr), ostream_iterator<decltype(arr[0])>(cout, " "));*/
	
	std::vector<ab> arr;
	for (int i = 0; i < 100; ++i)
	{
		arr.emplace_back( i);
	};
	auto del_begin = 
    std::partition(arr.begin(),arr.end(),[](auto i)
	{return !(i.a %2); });

	for_each(del_begin, std::end(arr), [](auto d) { d;  });

	arr.erase(del_begin, std::end(arr));
	
	/*std::copy(arr.begin(), arr.end(),std::ostream_iterator<ab>
		(std::cout, " ")); */

	std::shared_ptr<int> aa = make_shared<int>(1);
	if constexpr (std::is_pointer_v<decltype(aa)>)
	{
		std::cout << "포인터? ";
	}
	else
	{
		std::cout << "포인터 아님? ";
	}; 
	std::pair<const int, int> a;
	std::pair<const int, int> b ;
	
	std::cout << accumulate(std::istream_iterator<int>(cin), std::istream_iterator<int>(),
		0);
	std::cout << " wqeqwe qw "; 
	std::vector<int> qwe{ 1,2,3,4,5,6,777,8,9,10 };
	
	auto foo = []<typename T>(const T & element)
	{
		static T dest;
		class a {
		public:
			T data;
			a(T a) :data{ a } {};
			void function() 
		{
			T abc(123);
			std::cout << abc << " " << abc << std::endl;
		}
		}; 
		dest += element;
		
		return new a(dest);
	};
	foo = for_each(begin(qwe), end(qwe),foo);
	auto dd = foo(int());
	dd->function(); 
	dd->data; 

	//std::random_device rd;

	//std::map<int, int> A = { {1,1},{1,1} ,{4,5},{6,7} };

	////random_device rd;

	//
	
	//copy(begin(A), end(A), ostream_iterator<int>(cout, " "));
}