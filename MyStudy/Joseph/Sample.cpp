//#include "..\ScoreBoard\LinkedList.h"
//#include <iostream>
//using namespace std;
//
//template<typename T>
//struct Node
//{
//public:
//	T Data;
//	Node<T>* Next;
//	Node<T>* Prev;
//	Node<T>(T&& ParamData) :
//		Data(std::move  ( ParamData/* 파라미터로 넘긴 이후 접근 하지말기*/) ),
//		Next(nullptr), 
//		Prev(nullptr) {};
//	Node<T>(const T& ParamData) :
//		Data((ParamData)),
//			Next(nullptr),
//			Prev(nullptr) {};
//};
//template <typename T>
//class LinkedList
//{
//public:
//	uint32_t size = 0;
//	Node<T>* Head = nullptr;
//	Node<T>* Tail = nullptr; 
//
//	template<class T>
//	inline LinkedList<T>::Node<T>* 
//	LinkedList<T>::SearchDataNode(const T& Search) const
//	{
//		return nullptr;
//	}
//
//	LinkedList<T>() = default;
//
//	void Print()const 
//	{};
//
//	void Init(const T&ParamData)
//	{
//		if (size)
//		return; 
//
//		size++;
//		Head = new Node<T>(ParamData);
//	};
//	/*void Init(T&&ParamData)
//	{
//		if (size)
//		return; 
//
//		size++; 
//		Head  =  new Node<T>(ParamData);
//	};*/
//	inline bool IsEmpty()const
//	{
//		return !size; 
//	};
//	inline uint32_t Size()const 
//	{
//		return size; 
//	};
//	//void Insert( /*papapap */T&& ParamData,uint32_t OffSet = 0)const 
//	//{
//	//	if (IsEmpty())
//	//	{
//	//		Init( ParamData   );
//	//		return;
//	//	};
//	//	if (OffSet == 0)
//	//	{
//	//		back_Insert(std::move ( ParamData   ) );
//	//		return; 
//	//	}
//
//	//	Node<T>* Current  = nthNode(OffSet);
//	//	if (Current == nullptr)return; 
//
//	//	Current->Prev->Next = Current->Next;
//	//	Current->Next->Prev = Current->Prev;
//	//	delete Current;
//	//	Current = nullptr;
//	//	size++;
//	//};
//	void Insert(const T&ParamData,  uint32_t OffSet = 0)
//	{
//		if (IsEmpty())
//		{
//			Init(ParamData);
//			return; 
//		};
//		if (OffSet == 0)
//		{
//			back_Insert(ParamData);
//			return;
//		}
//
//		Node<T>* Current = nthNode(OffSet);
//		if (Current == nullptr)return;
//
//		Current->Prev->Next = Current->Next;
//		Current->Next->Prev = Current->Prev;
//		delete Current;
//		Current = nullptr;
//		size++;
//	};
//	void back_Insert(T ParamData)
//	{
//		Node<T>* InsertNode  = new Node<T>(ParamData);
//		Head->Prev = InsertNode;
//		InsertNode->Next = Head;
//
//		Tail->Next = InsertNode;
//		InsertNode->Prev = Tail;
//
//		Head = InsertNode;
//	};
//	//void back_Insert( T&&ParamData)const
//	//{
//	//	Node<T>* InsertNode = new Node<T>*(std::move ( ParamData   ) );
//	//	Head->Prev = InsertNode;
//	//	InsertNode->Next = Head;
//
//	//	Tail->Next = InsertNode;
//	//	InsertNode->Prev = Tail;
//
//	//	Head = InsertNode;
//	//};
//
//
//	void Erase(const uint32_t OffSet=0)const 
//	{
//		Node<T>* Target = nthNode(OffSet);
//		if (Target == nullptr)return; 
//
//		Target->Prev->Next = Target->Next;
//		Target->Next->Prev = Target->Prev;
//		
//		delete Target;
//		Target = nullptr; 
//	};
//
//	inline T GetData(const uint32_t OffSet=0)const 
//	{
//		return nthNode(OffSet)->Data;
//	};
//	/*virtual */
//	~LinkedList<T>() 
//	{
//		Node<T>* Target = Head;
//		while (Target)
//		{
//			Node<T>* Temp = Target;
//			Target = Target->Next;
//			delete Temp; 
//		};
//	};
//	template<typename T>
//	 friend ostream& operator<<(ostream& ConsoleOut, const LinkedList<T>& PrintList);
//private:
//	Node<T>* nthNode( uint32_t Offset=0) const 
//	{
//		if (!IsEmpty())
//			return nullptr;
//
//		Node<T>* ReturnVal = Head;
//
//		while (ReturnVal && Offset--)
//			ReturnVal = Head->Next; 
//
//		if (ReturnVal != nullptr)
//			return ReturnVal;
//		else
//			return nullptr;
//	};
///*
//	void front_Insert(const T&ParamData)const;
//	void front_Insert(T&&ParamData)const = */
//};
//template<typename T>
//inline ostream& operator<<(ostream& ConsoleOut, const LinkedList<T>& PrintList)
//{
//	PrintList.Print();
//	return ConsoleOut;
//};
//int main()
//{
//	LinkedList<int32_t> LList;
//	for(int i=0;i<10;++i)
//	LList.Insert(1);
//
//	cout << LList << endl;
//
//};