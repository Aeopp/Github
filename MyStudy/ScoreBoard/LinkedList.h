#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <functional>
#include "Utility.h"
#include "User.h"

template<class T>
class LinkedList
{
private:
	template<class Arg> 
	using FPtrType = std::function<bool(const Arg&, const T&)>;
	template<class T>
	struct Node
	{
		Node<T>& operator=(const Node&) = delete;
		Node<T>& operator=(Node&&) = delete;
		Node<T>(const Node&) = delete;
		Node<T>(Node&&) = delete;
		/*virtual */~Node<T>() = default;
	private:
		friend class LinkedList;
		T Data = User();
		Node<T>* Prev = nullptr;
		Node<T>* Next = nullptr;
		explicit Node<T>(const T& ParamData) :Data(ParamData) {};
		explicit Node<T>() = default;
	};

	Node<T>* Head;
	Node<T>* Tail;

	std::function<bool(const T&lhs,const T&rhs)>
	SortCompare;

	template<typename Arg>
	Node<T>* SearchNode(const Arg& Target,
	const FPtrType<Arg>& Compare)const;;

	inline Node<T>* SearchDataNode(const T& Search)const;;
public:
	explicit LinkedList<T>();;
	/*virtual*/ ~LinkedList<T>();;

	void SortInsert(const T& Data)const;
	void DeleteAll()const;

	 void Sort();
	 Node<T>* nthNode(uint32_t offset)const;
	 inline void SetSortFunction(
	std::function<bool(const  T& Lhs, const T& Rhs)>
		 SetSortFun);

	template<typename Arg>
	inline T& SearchData(const Arg& Target, 
	const FPtrType<Arg>& Compare)const;

	template<typename Arg>
	inline void Insert(const Arg& Target, 
	const FPtrType<Arg>& Compare,
	const T& Data)const;;

	template<typename Arg>
	inline T GetData(const Arg& Target, 
		const FPtrType<Arg>& Compare,
	const T& Search)const;;

	template<typename Arg>
	inline void SetData(const Arg& Target, 
		const FPtrType<Arg>& Compare,
	const T& ParamSetUp)const;

	template<typename Arg>
	 void Erase(const Arg& Target, 
		 const FPtrType<Arg>& Compare)const;

	inline void front_Insert(const T& Data)const;;
	inline void back_Insert(const T& Data)const;;
	 void InsertHelper(const T& Data, Node<T>*Mid, Node<T>*Rhs)const;
	inline bool Swap(const T& LhsTarget, const T& RhsTarget);
	 void Print()const;;
	inline bool IsEmpty() const;;
	
	inline T& operator[](uint32_t offset);

	 size_t getSize()const;

	 template<class T>
	 friend inline std::ostream& operator<<
		 (std::ostream& Conout, const LinkedList<T>& Llist);
};

template<class T>
inline std::ostream& operator<<(std::ostream& Conout, 
const LinkedList<T>& Llist)
{
	Llist.Print();
	return Conout;
}

template<class T>
 LinkedList<T>::Node<T>* LinkedList<T>::
	 SearchDataNode(const T & Search) const
{
	Node<T>* SearchPrev = Head;
	Node<T>* SearchNext;

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

template<class T>
 LinkedList<T>::LinkedList() : Head(new Node<T>), Tail(new Node<T>)
{
	Head->Prev = nullptr;
	Tail->Next = nullptr;

	Head->Next = Tail;
	Tail->Prev = Head;
	
	SetSortFunction([](const T& Lhs,const T& Rhs)->bool 
	{return Lhs < Rhs; });
}

 /*virtual*/
 template<class T>
 inline LinkedList<T>::~LinkedList()
 {
	 Node<T>* Target = Head->Next;

	 while (Target && Target != Tail)
	 {
		 Node<T>* NextTarget = Target->Next;
		 Utility::SAFE_DELETE(Target);
		 Target = NextTarget;
	 };

	 Utility::SAFE_DELETE(Head /*Target Is Head*/);

	 if (Tail != nullptr)
		 Utility::SAFE_DELETE(Tail);
 };

template<class T>
inline T& LinkedList<T>::operator[](uint32_t offset)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return nthNode(offset)->Data;
};

template<class T>
 size_t LinkedList<T>::getSize() const
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
template<class T>
 void LinkedList<T>::InsertHelper(const T& Data, Node<T>* Lhs, Node<T>* Rhs) const
{
	Node<T>* Inserter = new Node<T>(Data);
	/*(T Type Param Pass )*/

	Lhs->Next = Inserter;
	Inserter->Prev = Lhs;

	Rhs->Prev = Inserter;
	Inserter->Next = Rhs;
};


template<class T>
 void LinkedList<T>::Print() const
{
	Node<T>* PrintNode = Head->Next;

	while (PrintNode&&PrintNode != Tail)
	{
		std::cout << PrintNode->Data << std::endl;
		PrintNode = PrintNode->Next;
	};
};

template<class T>
inline bool LinkedList<T> ::IsEmpty() const
{
	return (Head->Next == Tail);
};

template<class T>
inline bool LinkedList<T>::Swap(const T& LhsTarget, const T& RhsTarget)
{
	auto* Lhs = SearchDataNode(LhsTarget);
	auto* Rhs = SearchDataNode(RhsTarget);

	assert((Lhs && Rhs) && "Swap Fail");
	/*return false */

	Utility::Swap(Lhs->Data, Rhs->Data);
	return true;
};

template<class T>
void LinkedList<T>::SortInsert(const T& Data) const
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
};

template<class T>
 void LinkedList<T>::Sort() 
{
	 T  key;
	int32_t  j = 0;
	int32_t i = static_cast<int32_t>(getSize() - 1);

	auto& Ref = *this;

	 for (i; i > 0; i--)
	 {
		 for (j = 0; j < i; j++ )
		 {
			 auto& Lhs = Ref[j];
			 auto& Rhs = Ref[j + 1];

			 if (SortCompare (Lhs, Rhs))
			 {
				 Utility::Swap(Lhs, Rhs);
			 }
		 };
	 }
};
template<class T>
 LinkedList<T>::Node<T>* LinkedList<T>::nthNode(uint32_t offset)const
{
	 Node<T>* Current = Head->Next;

	if (offset == 0 && Head->Next!=Tail) return Current;

	while (offset--&& Current->Next != Tail)
	{
		Current = Current->Next;
	};

	if (Current == Tail)
		return  nullptr; 

	return Current;
}
template<class T>
inline void LinkedList<T>::SetSortFunction( 
std::function<bool(const T& Lhs, const T& Rhs)> SetSortFun)
{
	SortCompare = SetSortFun;
};

template<class T>
template<typename Arg>
 LinkedList<T>::Node<T>* LinkedList<T>::SearchNode
 (const Arg& Target, const FPtrType<Arg>& Compare) const
{
	 Node<T>* SearchPrev = Head;
	 Node<T>* SearchNext;

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

template<class T>
template<typename Arg>
inline T & LinkedList<T>::SearchData(const Arg& Target ,
	const FPtrType<Arg>& Compare) const
{

	return SearchNode(Target,Compare)->Data;
}
template<class T>
template<typename Arg>
inline void LinkedList<T>::Insert(const Arg& Target, 
	const FPtrType<Arg>& Compare, const T& Data) const
{
	Node<T>* SearchPrev = SearchNode(Target, Compare);

	Node<T>* SearchNext = SearchPrev->Next;
	InsertHelper(Data, SearchPrev, SearchNext);
}
template<typename T>
template<typename Arg>
inline T LinkedList<T>::GetData(const Arg & Target,
	const FPtrType<Arg>& Compare, const T& Search) const
{
	Node<T>* RetVal = SearchNode(Target, Compare);
	return RetVal->Data;
};
template<typename T>
template<typename Arg>
inline void LinkedList<T>::SetData
(const Arg& Target, const FPtrType<Arg>& Compare,
	const T & ParamSetUp) const
{
	SearchNode(Target,Compare)->Data = ParamSetUp;
};

template<typename T>
template<typename Arg>
void LinkedList<T>::Erase(const Arg& Target,
	const FPtrType<Arg>& Compare) const
{
	Node<T>* Deleter = SearchNode<std::string>(Target, Compare);
	Node<T>* NPrev = Deleter->Prev;
	Node<T>* NNext = Deleter->Next;
	NPrev->Next = NNext;
	NNext->Prev = NPrev;

	Utility::SAFE_DELETE(Deleter);
};

template<typename T>
inline void LinkedList<T>::back_Insert(const T & Data) const
{
	InsertHelper(Data, Tail->Prev, Tail);

	
};
template<typename T>
inline void LinkedList<T>::front_Insert(const T & Data) const
{
	InsertHelper(Data, Head, Head->Next);
}
template<typename T>
void LinkedList<T>::DeleteAll() const
{
	Node<T>* Target = Head->Next;

	while (Target && Target != Tail)
	{
		Node<T>* NextTarget = Target->Next;
		Utility::SAFE_DELETE(Target);
		Target = NextTarget;
	};
}