

#include <iostream>
#include <vector> 
#include <iterator>
#include <algorithm>
#include <utility>
#include <numeric>
#include <string>
#include <sstream> 
#include <cctype>
#include <iterator>
#include <array>
#include <filesystem>
#include <any>
#include <numbers>
#include <queue>
#include <map>
#include <compare>
#include <set>
#include <regex>
using namespace std;


//
//template<auto k,typename T=decltype(a)>
//void foo(decltype(k) a)
//{
//	a = k;
//	T l = a;
//};
//using VotersMap = map<string, list<string>>;
//using DistricPair = pair<const string, list<string>>;
//// map 지역 이름 string key  해당 지역 선거인 명부 list<string>
//// 값으로 매핑
//set<string> getDuplicates(const VotersMap& votersByDistrict)
//{
//	template<class Arg>
//	std::function<void(int, float, double)> a;
//
//	list<string> allNames;
//	for (auto& district : votersByDistrict)
//	{
//		allNames.insert(end(allNames),begin(district.second),
//			end(district.second));
//	};
//	allNames.sort();
//	set<string> duplicates;
//	for (auto lit = cbegin(allNames); lit != cend(allNames); ++lit)
//	{
//		lit = adjacent_find(lit, cend(allNames));
//		if (lit == cend(allNames))
//		{
//			break;
//		};
//		duplicates.insert(*lit);
//	};
//	return duplicates;
//};
//set<string> getDuplicates(const VotersMap& votersByDistrict)
//{
//	set<string> allNames;
//	set<string> duplicates;
//	for (auto& district : votersByDistrict)
//	{
//		for (auto& name : district.second)
//		{
//			if (!allNames.insert(name).second)
//			{
//				duplicates.insert(name);
//			}
//		};
//	};
//	return duplicates;
//};
//void auditVoterRolls(VotersMap& votersByDistrict, const list<string>& convictedFelons)
//{
//	set<string> toRemove = getDuplicates(votersByDistrict);
//	toRemove.insert(cbegin(convictedFelons),
//
//		cend(convictedFelons));
//	
//	for_each(begin(votersByDistrict), end(votersByDistrict),
//		[&toRemove](DistricPair& district)
//		{
//			auto it = remove_if(begin(district.second),
//				end(district.second), [&toRemove](const string& name)
//				{
//					return (toRemove.count(name) > 0);
//				});
//			district.second.erase(it, end(district.second)); 
//		});
//	;
//};
//template<class T>
//class a
//
//{
//public:
//	a(T a) {};
//};
//int main()
//{
//	  list{"dsadas"s,"dasdas"s};
//
//	  a(1);
//};
#include <ratio>
#include <chrono>
#include <random>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iterator>
using namespace chrono;


//template<auto KK,typename T=decltype(KK)>
//void iteratorTraitsTest(T it)
//{
//	auto temp = *it;
//
//	
//	cout << typeid(temp).name() << endl;
//};
template<auto k=234>
void foo() {};

template<typename OutIter,typename InputIter,typename PredTy>
OutIter find_all(InputIter First, InputIter Last, OutIter Dest, 
PredTy Pred)
{
	while (First != Last)
	{
		if (Pred(*First))
		{
			*Dest = First;
			++Dest;
			++First;
		}
		else
			++First;
	};
	return Dest; 
};

//
//int main()
//{
//	vector vec{ 3,4,5,4,5,6,5,8 };
//	vector<decltype(vec)::iterator> matches;
//	auto a = find_all(begin(vec), end(vec),back_inserter(matches),
//		[](int i) {return i == 5; });
//
//	cout << "Found " << matches.size() << " matching elements: " << endl;
//
//	for (auto it : matches)
//	{
//		cout << *it << " at position " << (it - cbegin(vec)) << endl;
//	};
//
//};




