#include <iostream>
#include <optional>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <vector>
#include <string>

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
		subTrie(Iter First, Iter End)const
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

int main()
{
	Trie<std::string > Tester;
	Tester.insert({ "hi","how","are","you" });
	Tester.insert({"hi","i","am","great","thanks"});
	
	Tester.insert({ "what","are","you","doing"});
	Tester.insert({ "i","am","watching","a","movie" });

	std::cout << "기록된것 전부출력:\n";
	Tester.print();

	std::cout << "\n \"hi\":\n";
	if (auto Stance = Tester.subTrie(std::initializer_list<std::string>{"hi"});
		Stance)
	
		Stance->get().print();


	
}


