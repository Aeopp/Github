#include <iostream>
#include <unordered_map>
#include <vector>
#include <list>
#include <iterator> 
#include "iterator.h"
#include "hash_map.h"

using std::string;

int main()
{

	/*std::list<int>::const_iterator citer;
	std::list<int>::iterator iter;

	
	using hash_map_type = hash_map<int32_t,string>;
	using iter_type = hash_iterator<hash_map_type>;

	hash_map_type  hashmap;
	iter_type iter;
	std::cout << " One Step \n\n\n";
	for (int i = 1; i < 9; ++i)
	{
		if (const auto &[f, s] = hashmap.find(i); f == true)
		{
			auto& [pf, ps] = s;
			std::cout << pf << std::endl;
			std::cout << ps << std::endl;
		};
	}
		hashmap.insert({ 1,"홍길동" });
		hashmap.insert({ 2,"정상길" });
		hashmap.insert({ 3,"이상혁" });
		hashmap.insert({ 4,"조희건" });
		hashmap.insert({ 5,"이강현" });
		hashmap.insert({ 6,"이현아" });
		hashmap.insert({ 7,"이하나" });
		hashmap.insert({ 8,"김진경" });

		std::cout << " Two Step \n\n\n";

		for (int i = 1; i < 9; ++i)
		{
			if (const auto &[f, s] = hashmap.find(i); f == true)
			{
				auto& [pf, ps] = s;
				std::cout << pf << std::endl;
				std::cout << ps << std::endl;
			};
		}
		hashmap.erase(1);
		hashmap.erase(2);
		hashmap.erase(3);
		hashmap.erase(4);
		std::cout << " Third Step \n\n\n";
		for (int i = 1; i < 9; ++i)
		{
			if (const auto&[f, s] = hashmap.find(i); f == true)
			{
				auto& [pf, ps] = s;
				std::cout << pf << std::endl;
				std::cout << ps << std::endl;
			};
		};

		hashmap.rehash(64);

		std::cout << " Four Step \n\n\n";

		for (int i = 1; i < 9; ++i)
		{
			if (const auto& [f, s] = hashmap.find(i); f == true)
			{
				auto& [pf, ps] = s;
				std::cout << pf << std::endl;
				std::cout << ps << std::endl;
			};
		};

		std::cout << " Five Step \n\n\n";

		std::cout << "============= \n \n "  << std::endl;

		 auto hash_begin = std::begin(hashmap);
		 auto hash_end = std::end (hashmap);
		while (hash_begin != hash_end)
		{
			auto &[f, s] = *hash_begin; 
			std::cout << f << std::endl;
			std::cout << s << std::endl;
			++hash_begin;
		}*/

}

