#include<iostream>
#include <algorithm> 
#include <numeric>
using namespace std;
constexpr int32_t INT32MAX = std::numeric_limits<int32_t>::max();

int main()
{
	int32_t input;
	cin >> input;
	const int32_t n = input; 
	int32_t n3, n5, n53, n35, nn;
	n3 = n5 = n53 = n35 = nn = INT32MAX;
	if (n % 3 == 0)
		n3 = n / 3;
	if (n % 5 == 0)
		n5 = n / 5;
	if (n % 5 % 3 == 0)
		n53 =  (n/5 )+ ((n % 5) / 3);
	if ( n % 3 % 5 == 0)
		n35 =  (n/3 ) +  ((n % 3) / 5);
	int32_t multi = 1;
	while (n>(multi*5))
	{
		if (((n - multi * 5) % 3) == 0)
		{
			nn = multi+ ((n - (multi * 5)) / 3);
		};
		multi++;
	};
	// std::vector<int32_t> te = { n3,n5,n53,n35,nn };
	// std::initializer_list<int32_t>  il = { n3, n5, n53, n35 };
	int32_t minele = std::min({ n3,n5,n53,n35,nn });
	if (minele == INT32MAX)
		cout << -1;
	else
		cout << minele;
};