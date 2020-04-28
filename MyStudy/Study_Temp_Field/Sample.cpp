#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
// using namespace std::string_literals;
using namespace std;

template<typename M>
void print(const M& m) {
	cout << "Race placement:\n"; 
	for (const auto& [placement, driver] : m) {
		cout << placement << ":" << driver << endl; 
		
	};  
};
/*
C++17 에 새로이 추가된 Extract 함수를 이용해 노드를 직접 추출해 조작 가능.
해쉬,셋,맵 연관컨테이너라면 전부 활용 가능하며 이 기능을 활용하면
할당자의 도움을 필요로 하지 않으므로 불필요한 할당비용을 회피할수 있다.
extract(Iterator pos) , extract(key _key) 이터레이터와 키 값의
오버로딩 버전이 있으며 존재하지 않는 키의 노드타입은 비어있는 노드가
반환되고 이 인스턴스에 어떠한 함수를 호출하든 정의되지 않은 동작이므로
키가 존재하는것이 보장할수 없다면 empty 로 검사를 반드시하자

extract 로 노드를 추출한다음 key를 스왑하고 다시 move로 노드를
삽입하는 것은 기존에 맵의 키값을 바꾸고 싶었을 경우 더욱 빠른연산이
가능해져 매우 좋아보임

노드타입관 호환은 같은 연관 컨테이너 종류의 unique <-> multi 버전끼리만
노드가 호환이 된다 ex) set<->multiset 가능 set<->map !! 에러

해쉬의 경우도 마찬가지
C++17 에 try_emplace 기능도 생겼다.

*/


int main() {
	map<int, string> race_placement{
	{1,"Mario" } , {2,"Luigi"},
	{3,"Bowser" } ,  {4,"Peach"},    {5,"Yoshi" } ,{6,"Koo pa" } ,
	{ 7,"Toad " } ,   { 8, "Donkey Kong Jr." } };
	print(race_placement);

	auto a(race_placement.extract(3));
	auto b(race_placement.extract(8));

	std::swap(a.key(), b.key()); 


	// C++ 17 에 새로이 생긴  node_type 의 r_value 레퍼런스를 
	// 파라미터로 받는 insert 
	race_placement.insert(move(a));
	race_placement.insert(move(b));

	print(race_placement);

	map<int,int> _map{ {4,4} }; 
	auto _map_lhs = _map.extract(1);
	
	set<int, int> multi_map{ {4,4} };
	auto _multimap_lhs = multi_map.extract(1);

	unordered_map<int, int> _hash{ {7,7} };
	auto _hash_node = _hash.extract(7);

	_hash.insert(move(_hash_node));

	
};