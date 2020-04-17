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
using namespace std;
struct A
{
	friend void operator<<(ostream& Out, const A& t)
	{
		Out << "Iteratable    ";
	};
};
#include <queue>
int main()
{
	std::random_device rd;

	std::map<int, int> A = { {1,1},{1,1} ,{4,5},{6,7} };

	//random_device rd;

	

	copy(begin(A), end(A), ostream_iterator<int>(cout, " "));
}