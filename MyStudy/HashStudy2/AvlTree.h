#pragma once
#include <iostream>
#include <math.h>
using namespace std;
#ifndef max
#define max(a,b) ( ((a) >(b)) ?( a) : b )
#endif


class Node
{
private:
	Node* Left;
	Node* Right;
	int Key;
	int Height;
public:
	Node(const int PKey) : Left{ nullptr }, Right{ nullptr }, Key{ PKey }, Height{ 1 } {};
	// Node() {};
};

class  AvlTree
{
	int GetHeight(Node* PNode);
	int GetBalance(Node* PNode);
	Node* UpdateHeight(Node* PNode);
	Node* NewNode(int PKey);
	Node* Insert(Node* PRoot, int PKey);
	Node* LeftRotate(Node* PRoot);
	Node* RightRotate(Node* PRoot);

	Node* MinValueNode(Node* PNode);
	Node* DeleteNode(Node* PRoot, int PKey);
	void PrintAll(Node*PRoot);
	void PreOrder(Node*PRoot);
public:
	AvlTree();
	~AvlTree();
};
