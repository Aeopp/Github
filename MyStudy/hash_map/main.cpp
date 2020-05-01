#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <iterator> 
#include <map>
#include "iterator.h"
#include "hash_map.h"
#include <memory>
#include <functional>

using std::string;
//
//template<typename f_arg,typename s_arg>
//std::ostream& operator<<(std::ostream& out,const std::pair< f_arg, s_arg>
//& rhs)
//{
//	out << rhs.first << std::endl;
//	out << rhs.second << std::endl;
//	return out; 
//};
//template<typename f_arg, typename s_arg>
//std::ostream& operator<<(std::ostream& out, const std::pair<const f_arg,const s_arg>
//	& rhs)
//{
//	out << rhs.first << std::endl;
//	out << rhs.second << std::endl;
//	return out;
//};
//struct A
//{
//	int first = 1;
//	int second = 1;
//	friend std::ostream& operator<<(std::ostream& out, A& rhs);
//};
//std::ostream& operator<<(std::ostream& out,A& rhs)
//{
//	out << rhs.first << std::endl;
//	out << rhs.second << std::endl;
//	return out;
//};
class A
{
public :
	void foo()const&&{ std::cout << " const&& ";  };
	void foo()&&{ std::cout << " && ";  };
	void foo()const& { std::cout << " const& "; };
	void foo()&{ std::cout << " & "; };
};
int main()
{
	
	/*std::vector<int> integer;
	std::insert_iterator(integer, integer.begin());*/

	using hash_map_type = hash_map<int32_t, string>;

	hash_map_type  hashmap;

	hashmap.insert(std::pair(1, "A"));
	hashmap.insert(std::pair(2, "AB"));
	hashmap.insert(std::pair(2, "BA"));
	hashmap.insert(std::pair(3, "ABC"));
	hashmap.insert(std::pair(3, "BCA"));
	hashmap.insert(std::pair(3, "QWE"));
	hashmap.insert(std::pair(4, "SDAX"));
	hashmap.insert(std::pair(4, "SDAX"));
	hashmap.insert(std::pair(4, "WQED"));
	hashmap.insert(std::pair(4, "EWFD"));
	
	hashmap.erase(4);
	hashmap.erase(4);
	hashmap.erase(4);
	hashmap.erase(4);

	hash_map_type hash_map
	(std::begin(hashmap), std::end(hashmap));
	
	/* auto [f, s] = hash_map.equal_range(3);
	 if (f != std::end(hash_map))
	 {
		 std::cout << "찾음";
		 while (f != s)
		 {
			auto [fi, se] = *f;
			std::cout << fi << " " << se << std::endl;
			++f;
		 }; 
	 }
	 else
		 std::cout << "못찾음";*/

	 std::for_each(std::begin(hash_map), std::end(hash_map),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });

	 hash_map_type b{ {111,"qwe"} ,{222,"asd"} ,{333,"qwe"} };

	 std::for_each(std::begin(b), std::end(b),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });

	 b.insert({ { 777,"Lucky Seven !! " }, { 444,"$$$" } });

	 std::for_each(std::begin(b), std::end(b),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });

	 b.insert(std::begin(hashmap), std::end(hashmap));
	 std::cout << "\n\n\n\n\n";
	 if (auto find_iter = b.find(8658956);
		 find_iter != std::end(b))
	 {
		 auto [f, s] = *find_iter;
		 std::cout << f << " "   << s << std::endl;
	 };
	 std::for_each(std::begin(b), std::end(b),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });

	 decltype(b) def;
	 def.rehash(b.size());

	 auto inserter = std::insert_iterator<decltype(def)>(def, std::begin(def));
	 std::remove_copy_if(std::begin(b), std::end(b), inserter,
		 []( auto& element) {return true;  });

	 std::cout << "refefef " << b.size() << " ";

	 std::for_each(std::begin(def), std::end(def),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });

	 std::for_each(std::begin(b), std::end(b),
		 [](const auto& element) {std::cout << element.first << " "
		 << element.second << std::endl; });
};



