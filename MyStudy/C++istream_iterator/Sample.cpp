#include <iterator>
#include <string>
#include <iostream>
#include <set> 
#include <vector>
#include <execution>
using namespace std;
struct foo {
	void operator()(string a) {
		std::cout << "wqeqweqweqwe";
		cout << a;
	};
	void operator++() {}; 
	void operator=(string b) { (b); };
};

template<typename It>
void mycopy(It first,It end) {
	while (first != end) {
		//string temp = *first;
		std::cout << *first << " ";
		++first;
	};
};

int main() {
	set<string> q;
	mycopy(istream_iterator<string>{cin}, {});
	copy(istream_iterator<string>(cin), istream_iterator<string>(),
		inserter(q,begin(q))); 
	
	for (auto w : q)
		cout << w << " "; 


	set<string> _set{ "ABC"s,"ZXC"s,"QWE"s };
	vector<string> _vector; 

	_vector.resize(_set.size());

	move(std::execution::par_unseq,
		begin(_set), end(_set), begin(_vector));
	
	for (auto q : _set)
		cout << q << " ";
	for (auto q : _vector)
		cout << q << " ";

	
};
