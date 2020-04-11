#include <iostream>
#include <xutility>
#include <numbers>
#include <algorithm>
#include <string>
#include <map>
#include "hash_map.h"
using namespace std;

template<typename  Ty,typename _Ty>
bool IsEqual(const Ty& Lhs,const _Ty& Rhs)
{
	return (
		Lhs.size() == Rhs.size() &&
		_STD equal(Lhs.begin(), Lhs.end(), Rhs.begin()));
};

////template <class _Ty, class _Alloc>
////_NODISCARD bool operator==(const vector<_Ty, _Alloc>& _Left, 
//const vector<_Ty, _Alloc>& _Right) {
////	return _Left.size() == _Right.size()
////		&& 
//_STD equal(_Left._Unchecked_begin(), _Left._Unchecked_end(), 
//	_Right._Unchecked_begin());
////}

int main()
{
	//hash_map<string, int> myHash;
	//myHash.insert(make_pair("KeyOne", 100));
	//myHash.insert(make_pair("KeyTwo", 200));
	//myHash.insert(make_pair("KeyThree", 300));

	HashMap<string, int> myHash{
			{ "KeyOne", 100 },
			{ "KeyTwo", 200 } };

	myHash.insert({
			{ "KeyThree", 300 },
			{ "KeyFour", 400 } });

	for (auto it = myHash.cbegin(); it != myHash.cend(); ++it) {
		// Use both -> and * to test the operations
		cout << it->first << " maps to " << (*it).second << endl;
	}

	cout << "----" << endl;

	auto found = myHash.find("KeyThree");
	if (found != end(myHash))
	{
		cout << "Found KeyThree: value = " << found->second << endl;
	}

	cout << "----" << endl;

	// Print elements using range-based for loop
	for (auto& p : myHash) {
		cout << p.first << " maps to " << p.second << endl;
	}

	cout << "----" << endl;

	// Create a map with all the elements in the hashmap
	map<string, int> myMap(cbegin(myHash), cend(myHash));
	for (auto& p : myMap) {
		cout << p.first << " maps to " << p.second << endl;
	}

	hash_map<string, int> myHash2;
	myHash.swap(myHash2);

	hash_map<string, int> myHash3(std::move(myHash2));

	cout << myHash3.size() << endl;
	cout << myHash3.max_size() << endl;

	return 0;
};

