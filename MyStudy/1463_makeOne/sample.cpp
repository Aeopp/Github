#include <utility>
#include <array>
#include <cmath>
#include <iostream>
using namespace std;
// 첫째 줄에 1보다 크거나 같고, 10^6보다 작거나 같은 정수 N이 주어진다.
namespace
{
	constexpr size_t _pow(size_t  base, size_t exponent)
	{
		return exponent == 0 ? 1.0 : base * _pow(base, exponent - 1);
	}
	constexpr auto epslion = std::numeric_limits<float_t>::epsilon();
	constexpr auto max_number = std::numeric_limits<uint32_t>::max();
	     /*constexpr    10^6 */     /*0, 1,2,3*/
	array<uint32_t, _pow(10, 6)+1> arr{ max_number,0,1,1, };
};
constexpr void foo()
{
	for (int32_t i = 4; i <= _pow(10, 6); ++i)
	{
		float_t dvs_2 = static_cast<float>(i) / 2;
		float_t dvs_3 = static_cast<float>(i) / 3;

		dvs_2 = abs(dvs_2 - floor(dvs_2)) > epslion ? 0 : dvs_2;
		dvs_3 = abs(dvs_3 - floor(dvs_3)) > epslion ? 0 : dvs_3;
		arr[i] = (min({ arr[i - 1ul],arr[dvs_2],arr[dvs_3] }) + 1ul);
	};
}
int main()
{
	foo();
	size_t n;
	cin >> n;

	//for (int32_t i = 4; i <= n; ++i)
	//{
	//	float_t dvs_2,dvs_3;
	//	dvs_2 = static_cast<float>(i) / 2;
	//	dvs_3 = static_cast<float>(i) / 3;
	//	
	//	dvs_2 = abs(dvs_2 - floor(dvs_2)) > epslion ? 0 : dvs_2;
	//	dvs_3 = abs(dvs_3 - floor(dvs_3)) > epslion ? 0 : dvs_3;
	//	arr[i] = (min({ arr[i-1ul],arr[dvs_2],arr[dvs_3] }) + 1ul);
	//};
	//
	std::cout << arr[n];
}

