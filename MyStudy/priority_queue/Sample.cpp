#include <queue>
#include <iostream>
#include <tuple>
#include<string>
using namespace std;

int main() {
	using item_type = std::pair<int32_t, string >; 

	priority_queue<item_type> q;
	std::initializer_list<item_type> initlist = { {1,"dishes"},{2,"ok"} };
	for (auto&& inse : initlist)
		q.emplace(inse);


};