#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>__msvc_all_public_headers.hpp
#include <istream>__msvc_all_public_headers.hpp
#include <complex>_dbdao.h
#include <numeric>__msvc_all_public_headers.hpp
template<typename _Ty>
class Trie
{
public:
	template<typename Iter>
	void insert(Iter First, Iter End)
	{
		if (First == End) { return; }
		Tries[*First].insert(std::next(First), End); 
	};
	template<typename _Contain>
	void insert(const _Contain& container)
	{
		insert(std::begin(container), std::end(container)); 
	}
	void insert(const std::initializer_list<_Ty>& InitList)
	{
		insert(std::begin(InitList), std::end(InitList)); 
	}
	void print(std::vector<_Ty>& Vec) const
	{
		if(Tries.empty())
		{
			std::copy(std::begin(Vec), std::end(Vec),
				std::ostream_iterator<_Ty>{std::cout, " "});
			std::cout << '\n';
		}
		for(const auto&[First,Second] : Tries )
		{
			Vec.push_back(First);
			Second.print(Vec);
			Vec.pop_back();
		}
	}
	void print() const
	{
		std::vector<_Ty > Vec;
		print(Vec);
	}
	template<typename Iter>
	std::optional<std::reference_wrapper<const Trie>>
		subTrie(Iter First,Iter End)const
	{
		if (First == End) { return std::ref(*this); }
		auto found(Tries.find(*First));
		if (found == std::end(Tries)) { return {}; }

		return found->second.subTrie(std::next(First), End);
	};
	template<typename _Contain>
	auto subTrie(const _Contain& container)
	{
		return subTrie(std::begin(container), std::end(container));
	}
private:
	std::map<_Ty, Trie> Tries;
};
static void prompt() {
	std::cout << "Next input please:\n";
};


using namespace std;
int main()
{
	
}
	
