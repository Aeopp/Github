#include <iostream>
#include <list>
#include<vector> 
#include <string>
#include <algorithm>
#include <iterator>
using namespace std; 


int main()
{
	std::list a{ 1,2,3,4,5,6,7,8,9,10 };
	std::list<string> b; 
	
	transform(a.begin(), a.end(), back_inserter(b),  
	[](const auto&element )
		{
			return " qweqweqwe";  
		});
	copy(b.begin(), b.end(), 
	std::ostream_iterator<decltype(*b.begin())>(std::cout, " "));

}