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
C++17 �� ������ �߰��� Extract �Լ��� �̿��� ��带 ���� ������ ���� ����.
�ؽ�,��,�� ���������̳ʶ�� ���� Ȱ�� �����ϸ� �� ����� Ȱ���ϸ�
�Ҵ����� ������ �ʿ�� ���� �����Ƿ� ���ʿ��� �Ҵ����� ȸ���Ҽ� �ִ�.
extract(Iterator pos) , extract(key _key) ���ͷ����Ϳ� Ű ����
�����ε� ������ ������ �������� �ʴ� Ű�� ���Ÿ���� ����ִ� ��尡
��ȯ�ǰ� �� �ν��Ͻ��� ��� �Լ��� ȣ���ϵ� ���ǵ��� ���� �����̹Ƿ�
Ű�� �����ϴ°��� �����Ҽ� ���ٸ� empty �� �˻縦 �ݵ������

extract �� ��带 �����Ѵ��� key�� �����ϰ� �ٽ� move�� ��带
�����ϴ� ���� ������ ���� Ű���� �ٲٰ� �;��� ��� ���� ����������
�������� �ſ� ���ƺ���

���Ÿ�԰� ȣȯ�� ���� ���� �����̳� ������ unique <-> multi ����������
��尡 ȣȯ�� �ȴ� ex) set<->multiset ���� set<->map !! ����

�ؽ��� ��쵵 ��������
C++17 �� try_emplace ��ɵ� �����.

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


	// C++ 17 �� ������ ����  node_type �� r_value ���۷����� 
	// �Ķ���ͷ� �޴� insert 
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