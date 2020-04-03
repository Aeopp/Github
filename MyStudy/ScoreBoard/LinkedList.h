#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include "User.h"
struct Node;
class LinkedList;
using T = User;
class LinkedList
{
	using T = User;
	using FunType = std::function<bool(const T&Lhs, const T&Rhs)>;
private:
	struct Node
	{
	private:
		friend class LinkedList;
		using T = User;
		T Data = User();
		Node* Prev = nullptr;
		Node* Next = nullptr;
		Node(const T& ParamData) :Data(ParamData) {};
		Node() {};
	};
	struct Node* Head;
	struct Node* Tail;

	FunType SortCompare;

	template<typename Ty>
	inline Node* SearchNode(const Ty& Target,
	std::function<bool(const Ty&Lhs,const T& Rhs)>Compare)const;;
	

	inline Node* SearchDataNode(const T& Search)const;;
public:
	LinkedList();;
	/*virtual*/ ~LinkedList()
	{
		Node* Target = Head->Next;

		while (Target && Target != Tail)
		{
			Node* NextTarget = Target->Next;
			Utility::SAFE_DELETE(Target);
			Target = NextTarget;
		};

		Utility::SAFE_DELETE(Head /*Target Is Head*/);

		if (Tail != nullptr)
			Utility::SAFE_DELETE(Tail);
	};

	void SortInsert(const T& Data)const;
	void DeleteAll()const;

	inline void Sort();
	inline Node* nthNode(uint32_t offset)const;
	inline void SetSortFunction(const FunType&);

	template<typename Ty>
	inline T& SearchData(const Ty& Target,std::function<bool(const Ty&Lhs,const T& Rhs)>Compare)const;
	/*inline T& SearchData(const T& Search)const;*/

	template<typename Ty>
	inline void Insert(const Ty& Target, std::function<bool(const Ty&Lhs, const T& Rhs)>Compare,
	const T& Data)const;;

	template<typename Ty>
	inline T GetData(const Ty& Target, std::function<bool(const Ty&Lhs, const T& Rhs)>Compare, 
	const T& Search)const;;

	template<typename Ty>
	inline void SetData(const Ty& Target, std::function<bool(const Ty&Lhs, const T& Rhs)>Compare, 
	const T& ParamSetUp)const;

	template<typename Ty>
	inline void Erase(const Ty& Target, 
	std::function<bool(const Ty&Lhs, const T& Rhs)>Compare)const;

	inline void front_Insert(const T& Data)const;;
	inline void back_Insert(const T& Data)const;;
	inline void InsertHelper(const T& Data, Node*Mid, Node*Rhs)const;
	inline bool Swap(const T& LhsTarget, const T& RhsTarget);
	inline void Print()const;;
	inline bool IsEmpty() const;;
	
	inline T& operator[](uint32_t offset);
	inline size_t getSize()const;

	friend inline std::ostream& operator<<(std::ostream& Conout, const LinkedList& Llist);
};

inline std::ostream& operator<<(std::ostream& Conout, const LinkedList& Llist)
{
	Llist.Print();
	return Conout;
	// TODO: 여기에 반환 구문을 삽입합니다.
}


inline LinkedList::Node * LinkedList::SearchDataNode(const T & Search) const
{
	Node* SearchPrev = Head;
	Node* SearchNext;

	while (SearchPrev &&  (Search!=  SearchPrev->Data ))
	{
		SearchPrev = SearchPrev->Next;
	};
	if (SearchPrev == nullptr)
	{
		/*assert(false && " 데이터를 찾을 수 없습니다.");*/
		std::cout << "데이터를 찾을 수 없습니다 . : ";
		return nullptr;
	};
	return SearchPrev;
};

inline LinkedList::LinkedList() : Head(new Node), Tail(new Node)
{
	Head->Prev = nullptr;
	Tail->Next = nullptr;

	Head->Next = Tail;
	Tail->Prev = Head;
	
	SetSortFunction([](const T& Lhs,const T& Rhs)->bool 
	{
		return Lhs <= Rhs; 
	});
};

//inline T LinkedList::GetData(const T & Search) const
//{
//	Node* RetVal = SearchNode(Search);
//	return RetVal->Data;
//};
//
//inline void LinkedList::SetData(const T & Search, const T & ParamSetUp) const
//{
//	SearchNode(Search)->Data = ParamSetUp;
//	// TODO :: 데이터를 가져와서 무엇인가를 한다........
//}

inline T &LinkedList::operator[](uint32_t offset)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return nthNode(offset)->Data;
}
inline size_t LinkedList::getSize() const
{
	size_t RetVal = 0;
	auto* Current = Head->Next;

	while (Current!=Tail)
	{
		RetVal++;
		Current = Current->Next;
	};

	return RetVal;
};

inline void LinkedList::InsertHelper(const T& Data, Node * Lhs, Node * Rhs) const
{
	Node* Inserter = new Node(Data);/*(T Type Param Pass )*/

	Lhs->Next = Inserter;
	Inserter->Prev = Lhs;

	Rhs->Prev = Inserter;
	Inserter->Next = Rhs;
};

//inline void LinkedList::Erase(const T & Search)const
//{
//	Node* Target = SearchNode(Search);
//	Node* NPrev = Target->Prev;
//	Node* NNext = Target->Next;
//	NPrev->Next = NNext;
//	NNext->Prev = NPrev;
//
//	Utility::SAFE_DELETE(Target);
//};
inline void LinkedList::Print() const
{
	Node* PrintNode = Head->Next;
	while (PrintNode&&PrintNode != Tail)
	{
		std::cout << PrintNode->Data << std::endl;
		PrintNode = PrintNode->Next;
	};
};

inline bool LinkedList::IsEmpty() const
{
	return (Head->Next == Tail);
};

//inline LinkedList::Node*LinkedList::SearchNode(const T& Search)const
//{
//	Node* SearchPrev = Head;
//	Node* SearchNext;
//
//	while (SearchPrev && SearchPrev->Data != Search)
//	{
//		SearchPrev = SearchPrev->Next;
//	};
//	if (SearchPrev == nullptr)
//	{
//		/*assert(false && " 데이터를 찾을 수 없습니다.");*/
//		std::cout << "데이터를 찾을 수 없습니다 . : ";
//		return nullptr;
//	};
//	return SearchPrev;
//}

inline bool LinkedList::Swap(const T & LhsTarget, const T & RhsTarget)
{
	auto* Lhs = SearchDataNode(LhsTarget);
	auto* Rhs = SearchDataNode(RhsTarget);

	assert((Lhs&&Rhs) && "Swap Fail");
	/*return false */

	Utility::Swap(Lhs->Data, Rhs->Data);
	return true;
}

inline void LinkedList::SortInsert(const T & Data) const
{
	if (IsEmpty())
	{
		front_Insert(Data);
		return; 
	};

	auto Current = Head->Next; 

	while (SortCompare(Data, Current->Data))
	{
		Current = Current->Next;
		if (Current == Tail)break;
	};
	InsertHelper(Data, Current->Prev, Current); 
}



inline void LinkedList::Sort() 
{
	int32_t i, j,n;  
	T key;
	const uint32_t ConSize = this->getSize(); 
	auto &Ref  =*this;
	for (i = 1; i < ConSize; i++) {
		key = Ref[i];
		for (j = i - 1; j >= 0 && SortCompare(Ref[j] ,key); j--) {
			Ref[j + 1] = Ref[j];
		}
		Ref[j + 1] = key;
	}
};

inline LinkedList::Node* LinkedList::nthNode(uint32_t offset)const
{
	Node* Current = Head->Next;

	if (offset == 0 && Head->Next!=Tail) return Current;

	while (offset--&& Current->Next != Tail)
	{
		Current = Current->Next;
	};

	if (Current == Tail)
		return  nullptr; 

	return Current;
}

inline void LinkedList::SetSortFunction(const FunType & SetSortFun)
{
	SortCompare = SetSortFun;
}
template<typename Ty>
inline LinkedList::Node * LinkedList::SearchNode
(const Ty & Target, std::function<bool(const Ty&Lhs, const T&Rhs)> Compare) const
{
	Node* SearchPrev = Head;
	Node* SearchNext;

	while (SearchPrev && Compare(Target, SearchPrev->Data))
	{
		SearchPrev = SearchPrev->Next;
	};
	if (SearchPrev == nullptr)
	{
		/*assert(false && " 데이터를 찾을 수 없습니다.");*/
		std::cout << "데이터를 찾을 수 없습니다 . : ";
		return nullptr;
	};
	return SearchPrev;
}
//template<typename Ty>
//inline Node * LinkedList::SearchNode(const Ty & Target, std::function<bool(const Ty&Lhs, const T&Rhs)> Compare) const
//{
//	
//
//}
template<typename Ty>
inline T & LinkedList::SearchData(const Ty& Target ,
std::function<bool(const Ty& Target ,const T&Rhs)> Compare) const
{
	//Node* Target = SearchNode(Search);
	//if (Target == nullptr) return;

	return SearchNode(Target,Compare)->Data;
}

template<typename Ty>
inline void LinkedList::Insert(const Ty & Target, std::function<bool(const Ty&Lhs, const T&Rhs)> Compare, const T & Data) const
{
	Node* SearchPrev = SearchNode(Target,Compare);

	Node* SearchNext = SearchPrev->Next;
	InsertHelper(Data, SearchPrev, SearchNext);
}

template<typename Ty>
inline T LinkedList::GetData(const Ty & Target, std::function<bool(const Ty&Lhs, const T&Rhs)> Compare, const T & Search) const
{
	Node* RetVal = SearchNode(Target,Compare);
	return RetVal->Data;
};

template<typename Ty>
inline void LinkedList::SetData(const Ty & Target, std::function<bool(const Ty&Lhs, const T&Rhs)> Compare, 
	const T & ParamSetUp) const
{
	SearchNode(Target,Compare)->Data = ParamSetUp;
};
template<typename Ty>
inline void LinkedList::Erase(const Ty & Target, 
	std::function<bool(const Ty&Lhs, const T&Rhs)> Compare) const
{
	Node * Deleter = SearchNode<std::string>(Target,Compare);
	Node* NPrev = Deleter->Prev;
	Node* NNext = Deleter->Next;
	NPrev->Next = NNext;
	NNext->Prev = NPrev;

	Utility::SAFE_DELETE(Deleter);
}

//inline T & LinkedList::SearchData(const T & Search) const
//{
//	//Node* Target = SearchNode(Search);
//	//if (Target == nullptr) return;
//	return SearchNode(Search)->Data;
//};

//inline void LinkedList::Insert(const T &Search, const T & Data) const
//{
//	Node* SearchPrev = SearchNode(Search);
//
//	Node* SearchNext = SearchPrev->Next;
//	InsertHelper(Data, SearchPrev, SearchNext);
//
//}
inline void LinkedList::back_Insert(const T & Data) const
{
	InsertHelper(Data, Tail->Prev, Tail);

	
};
inline void LinkedList::front_Insert(const T & Data) const
{
	InsertHelper(Data, Head, Head->Next);
}
