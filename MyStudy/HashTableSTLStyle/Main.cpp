

#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <functional>

template<typename T,typename Key=T>
class LinkedList
{
public:
	// Interface  
	inline void setcompare(CompareTy<Key> SetSortFun);
	void print()const;
	void clear()noexcept const;
	void sort();
	void insert       (const T& data)const;
	inline void insert(const Key& pKey, const T& data)const;
	void erase(const Key& pKey)noexcept const;
	inline T& find  (const Key& pkey)const;
	inline T& operator[](uint32_t offset);
	inline bool empty() const;
	inline void front_Insert(const T& data)const;
	inline void push_back(const T& data)const;
	size_t size()const;
	// Interface   








	using CompareTy = std::function<bool(const Key& lhs, const Key& rhs)>;
	CompareTy<Key> compare;
	explicit LinkedList<T, Key>();
	/*virtual*/~LinkedList<T, Key>();

	template<typename T,typename Key>
	friend inline std::ostream& operator<<
	(std::ostream& Conout, const LinkedList<T,Key>& Llist);
private:
	template<typename T>
	struct Node
	{
		Node<T>& operator=(const Node&) = delete;
		Node<T>& operator=(Node&&) = delete;
		Node<T>(const Node&) = delete;
		Node<T>(Node&&) = delete;
		/*virtual */~Node<T>() = default;
	private:
		friend class LinkedList;
		T data = T();
		Node<T>* prev = nullptr;
		Node<T>* next = nullptr;
		explicit Node<T>(const T& ParamData) : data(ParamData) {};
		explicit Node<T>() = default;
	};
	Node<T>* head;
	Node<T>* tail;
	uint64_t _size;
	// Convenience Method
	Node<T>* search_node(const Key& pKey)const;;
	inline bool node_swap(const T& lhsTKeyet, const T& rhsTKeyet);
	void insert_helper(const T& data, Node<T>* Mid, Node<T>* rhs)const;
	Node<T>* nth_node(uint32_t offset)const;
	inline bool equal(const Key& lhs, const Key& rhs) const;
};;
template<typename T,typename Key>
inline std::ostream& operator<<(std::ostream& Conout,
const LinkedList<T, Key>& Llist)
{
	Llist.print();
	return Conout;
};

template<typename T,typename Key>
LinkedList<T,Key>::
Node<T>* LinkedList<T,Key>::
search_node(const Key& pKey) const
{
	auto* current = head->next;

	while (current && current != tail)
	{
		if (equal(pKey, current->data))
			return current; 

		current = current->next;
	}
	return nullptr; 
}

template<typename T,typename Key>
LinkedList<T, Key>::LinkedList() : head(new Node<T>), tail(new Node<T>)
{
	head->prev = nullptr;
	tail->next = nullptr;

	head->next = tail;
	tail->prev = head;

	setcompare([]
	(const Key& lhs, const Key& rhs)->bool
	{return lhs < rhs; });
};

/*virtual*/
template<typename T,typename Key>
inline LinkedList<T,Key>::~LinkedList()
{
	Node<T>* deleter = head->next;

	while (deleter && deleter != tail)
	{
		Node<T>* nexttemp = deleter->next;
		delete deleter; 
		deleter = nexttemp;
	};

	delete head /*deleter Is head*/;
	delete tail;
};

template<typename T,typename Key>
inline T& LinkedList<T,Key>::operator[](const uint32_t offset)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return nth_node(offset)->data;
};

template<typename T,typename Key>
size_t LinkedList<T,Key>::size() const
{
	return _size;
};

template<typename T,typename Key>
void LinkedList<T,Key>::insert_helper
(T&& data,const Node<T>*& lhs,const Node<T>*& rhs) const
{
	auto* inserter = new Node<T>(std::forward<T>(data));
	/*(T Type Param Pass )*/

	lhs->next = inserter;
	inserter->prev = lhs;

	rhs->prev = inserter;
	inserter->next = rhs;
};


template<typename T,typename Key>
void LinkedList<T,Key>::print() const
{
	auto* PrintNode = head->next;

	while (PrintNode && PrintNode != tail)
	{
		std::cout << PrintNode->data << std::endl;
		PrintNode = PrintNode->next;
	};
};

template<typename T,typename Key>
inline bool LinkedList<T,Key> ::empty() const
{
	return (head->next == tail) && _size==0;
};

template<typename T,typename Key>
inline bool LinkedList<T,Key>::node_swap(const T& lhs, const T& rhs)
{
	auto* lhs = search_node(lhs);
	auto* rhs = search_node(rhs);
	if (lhs && rhs)
	{
		std::swap(lhs->data, rhs->data);
		return true;
	}
	else
		return false;
};

template<typename T,typename Key>
void LinkedList<T,Key>::
insert_sort(const T& data,const Key& pKey) const
{
	if (empty())
	{
		front_Insert(data);
		return;
	};

	auto current = head->next;

	while (compare(pKey,current->data))
	{
		current = current->next;
		if (current == tail)break;
	};

	insert_helper(data, current->prev, Current);
};

template<typename T,typename Key>
void LinkedList<T,Key>::sort()
{
	T  key;
	int32_t  j = 0;
	int32_t i = static_cast<int32_t>(size() - 1);

	auto& Ref = *this;

	for (i; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			auto& lhs = Ref[j];
			auto& rhs = Ref[j + 1];

			if (SortCompare(lhs, rhs))
			{
				Utility::node_swap(lhs, rhs);
			}
		};
	}
}
template<typename T, typename Key>
inline T& LinkedList<T, Key>::find(const Key& TKeyet) const
{
	// TODO: 여기에 return 문을 삽입합니다.
}
template<typename T, typename Key>
inline T LinkedList<T, Key>::getdata(const Key& TKeyet) const
{
	return T();
}
template<typename T, typename Key>
inline void LinkedList<T, Key>::insert(const Key& TKeyet, const T& data) const
{
}
template<typename T, typename Key>
void LinkedList<T, Key>::erase(const Key& pKey) const
{
}
template<typename T, typename Key>
inline void LinkedList<T, Key>::setcompare(CompareTy SetSortFun)
{
}
;
template<typename T,typename Key>
LinkedList<T,Key>::Node<T>* LinkedList<T,Key>::nth_node(uint32_t offset)const
{
	Node<T>* Current = head->next;

	if (offset == 0 && head->next != tail) return Current;

	while (offset-- && Current->next != tail)
	{
		Current = Current->next;
	};

	if (Current == tail)
		return  nullptr;

	return Current;
}
template<typename T, typename Key>
inline bool LinkedList<T, Key>::equal(const Key& lhs, const Key& rhs) const
{
	return (!compare(lhs,rhs) && !compare(rhs,lhs));
};
template<typename T,typename Key>
inline void LinkedList<T,Key>::setcompare(CompareTy<Key> pcompare)
{
	this->compare = pcompare;
};


template<typename T,typename Key>

inline T& LinkedList<T,Key>::find(const Key& TKeyet,
	const FPtrType<Key>& compare) const
{
	return search_node(TKeyet, compare)->data;
};
template<typename T,typename Key>
inline void LinkedList<T, Key>::insert(const Key& TKeyet,
	const FPtrType<Key>& compare, const T& data) const
{
	Node<T>* Searchprev = search_node(TKeyet, compare);
	Node<T>* Searchnext = Searchprev->next;
	insert_helper(data, Searchprev, Searchnext);
};

template<typename T,typename Key>
inline T LinkedList<T,Key>::GetData(const Key& TKeyet,
const FPtrType<Key>& compare, const T& Search) const
{
	Node<T>* RetVal = search_node(TKeyet, compare);
	return RetVal->data;
};

template<typename T,typename Key>
inline void LinkedList<T,Key>::SetData
(const Key& TKeyet, const FPtrType<Key>& compare,
	const T& ParamSetUp) const
{
	search_node(TKeyet, compare)->data = ParamSetUp;
};

template<typename T,typename Key>
void LinkedList<T,Key>::erase(const Key& TKeyet,
	const FPtrType<Key>& compare) const
{
	Node<T>* Deleter = search_node<std::string>(TKeyet, compare);
	Node<T>* Nprev = Deleter->prev;
	Node<T>* Nnext = Deleter->next;
	Nprev->next = Nnext;
	Nnext->prev = Nprev;

	Utility::SAFE_DELETE(Deleter);
};

template<typename T,typename Key>
inline void LinkedList<T,Key>::push_back(const T& data) const
{
	insert_helper(data, tail->prev, tail);


};

template<typename T,typename Key>
inline void LinkedList<T, Key>::front_Insert(const T& data) const
{
	insert_helper(data, head, head->next);
};

template<typename T, typename Key>
void LinkedList<T, Key>::insert(const T& data) const
{
}

template<typename T,typename Key>
void LinkedList<T, Key>::clear() const
{
	Node<T>* TKeyet = head->next;

	while (TKeyet && TKeyet != tail)
	{
		Node<T>* nextTKeyet = TKeyet->next;
		Utility::SAFE_DELETE(TKeyet);
		TKeyet = nextTKeyet;
	};
};

int main()
{
	
	/*HashMap<string, int> myHash;
	myHash.insert(make_pair("KeyOne", 100));
	myHash.insert(make_pair("KeyTwo", 200));
	myHash.insert(make_pair("KeyThree", 300));
	*/
	//HashMap<string, int> myHash{
	//		{ "KeyOne", 100 },
	//		{ "KeyTwo", 200 } };

	//myHash.insert({
	//		{ "KeyThree", 300 },
	//		{ "KeyFour", 400 } });
	
	//for (auto it = myHash.cbegin(); it != myHash.cend(); ++it) {
	//	// Use both -> and * to test the operations
	//	cout << it->first << " maps to " << (*it).second << endl;
	//}

	//cout << "----" << endl;

	//auto found = myHash.find("KeyThree");
	//if (found != end(myHash))
	//{
	//	cout << "Found KeyThree: value = " << found->second << endl;
	//}

	//cout << "----" << endl;

	//// Print elements using range-based for loop
	//for (auto& p : myHash) {
	//	cout << p.first << " maps to " << p.second << endl;
	//}

	//cout << "----" << endl;

	//// Create a map with all the elements in the hashmap
	//map<string, int> myMap(cbegin(myHash), cend(myHash));
	//for (auto& p : myMap) {
	//	cout << p.first << " maps to " << p.second << endl;
	//}

	//HashMap<string, int> myHash2;
	//myHash.swap(myHash2);

	//HashMap<string, int> myHash3(std::move(myHash2));

	//cout << myHash3.size() << endl;
	//cout << myHash3.max_size() << endl;

	//return 0;
};


