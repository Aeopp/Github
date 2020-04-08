#include <iostream>
#include <vector> 
#include <iterator>
#include <algorithm>
#include <utility>
#include <numeric>
#include <string>

int deleteDigit(int n) {
	using std::string;
	using std::to_string;
	using std::vector;

	const string str = to_string(n);
	std::vector<int32_t> vec(str.size());

	for (int32_t i = 0; i < str.size(); ++i)
	{
		string buf = str;
		//std::erase(buf,buf[i]);
		buf.erase(begin(buf) + i);
		vec[i] = (stoi(buf));
	};
	//for_each(begin(vec), end(vec),[](auto& e) {std::cout << e << " "; });
	
	return *max_element(begin(vec), end(vec));;

}
int main()
{
	std::cout<<deleteDigit(123456789);
};
