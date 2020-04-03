////  Binary trees are already defined with this interface:
// template<typename T>
// struct Tree {
//   Tree(const T &v) : value(v), left(nullptr), right(nullptr) {}
//   T value;
//   Tree *left;
//   Tree *right;
// };
//#include <vector>
//#include <algorithm>
//
//std::vector<int> vec;
//// aa->left = &Tree<int>(2);
///*
//	1
//   / \
//  2   2
// / \ / \
//3  4 4  3  */
//// 
//// 함수호출
//bool match = true;
//
//bool foo(Tree<int>* t)
//{
//	if (!t)
//		return true;
//	if (!t->left && !t->right)
//		return true;
//	if (!t->left || !t->right)
//		return false;
//
//	match = t->left->value == t->right->value;
//	if (match == false)
//		return false;
//};
//void travel(Tree<int>* t)
//{
//	if (t->left)
//		travel(t->left);
//	if (t)
//	{
//		vec.push_back(t->value);
//		std::cout << t->value << std::endl;
//	};	
//	// vec.push_back(t->value);
//	if (t->right)
//		travel(t->right);
//};
//bool isTreeSymmetric(Tree<int> * t) {
//	if (!t)
//		return true;
//	else
//		travel(t);
//
//	if (vec.size() == 1)
//		return true;
//	if (vec.size() % 2 == 0)
//		return false;
//
//
//	auto left = vec.begin();
//	auto right = vec.end();
//	
//	int l = 0;
//	int r = vec.size() - 1;
//	int m = vec.size() / 2;
//
//	while (l != m)
//	{
//		if (vec[l] != vec[r])
//		{
//			
//			return false;
//			
//		}
//		l++;
//		r--;
//	};
//	return true;
///*
//	for (int i = 0; i < 3; ++i)
//		cout << vec[i] << ' ';
//	cout << endl;
//	for (int i = 4; i < 7; ++i)
//	{
//		cout << vec[i] << ' ';
//	};
//*/
//
//	/*while (left!=right)
//	{
//		if (*left != *right)
//		{
////			return false;
////		};
//	};
//	return true;*/
//	auto itor = vec.begin() + (midsize+1);
//
//	std::vector<int> rhs(itor, vec.end());
//	std::reverse(rhs.begin(), rhs.end());
//
//	std::vector<int>lhs(vec.begin(),vec.begin() + (midsize-1));
//
//std::	cout << std::endl <<std:: endl << std::endl;
//for (const auto&Element : rhs)
//std::cout <<Element << ' ';
//
//std::cout << std::endl;
//
//
//for (const auto&Element : lhs)
//std::cout << Element << ' ';


 // return true;

//int main()
//{
//	Tree<int> aa(1);
//	Tree<int> al(2);
//	Tree<int> ar(2);
//
//	aa.left = &al;
//	aa.right = &ar;
//	  
//	al.left = &Tree<int>(3);
//	al.right = &Tree<int>(4);
//	  
//	ar.left = &Tree<int>(4);
//	ar.right = &Tree<int>(0);
//
//	  // travel(&aa);
//	 isTreeSymmetric(&aa);
//};
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
bool nocase_compare(char c1, char c2)
{
	return toupper(c1) == toupper(c2);
};

int main()
{
	std::string aa("AABBBBCCCCDDE");

	aa.erase(unique(aa.begin(), aa.end()), aa.end());

	std::cout << aa;


};