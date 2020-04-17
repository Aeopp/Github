#pragma once
#include <iostream>
#include <string>

template<typename Ty>
class List
{
public:
	// interface begin....
	void inline push_back(Ty&& param)
	{
		inserthelper(std::move(param), tail->prev, tail);
	};
	void inline push_back(const Ty& param)
	{
		inserthelper(param, tail->prev, tail);
	};
	void inline push_front(Ty&& param)
	{
		inserthelper(std::move(param), head, head->next);
	};
	void inline push_front(const Ty& param)
	{
		inserthelper(param, head, head->next);
	};
	bool insert(Ty&& param, const uint64_t offset)
	{
		auto target = nth_node(offset);
		if (target)
		{
			inserthelper(param, target, target->next);
			return true;
		}
		else
			return false;
	};
	void sort()noexcept;
	bool erase(const Ty& param);
	Ty& find(const Ty& param);
	int64_t inline size() const;
	Ty& operator[](const int64_t offset)
	{
		auto value = nth_node(offset);
		return value->element;
	};
	bool empty() const
	{
		return (head->next == tail) && (_size == 0);
	}
	void clear() noexcept
	{
		if (empty())return;

		auto* deleter = head->next;

		while (deleter && deleter != tail)
		{
			auto* nextdeleter = deleter->next;
			delete deleter;
			deleter = nextdeleter;
		};

		head->next = tail;
		tail->prev = head;
		_size = NULL;
	}
	// interface end....
	template<typename Ty>
	friend std::wostream& operator<<
		(std::wostream& out, const List<Ty>& target);;

	using value_type = Ty;
	using size_type = uint64_t;
	using difference_type = ptrdiff_t;
	using pointer = Ty*;
	using const_pointer = const Ty*;
	using reference = Ty&;
	using const_reference = const Ty&;

	List() :
		_size(0),
		head(new node<Ty>), tail(new node<Ty>)
	{
		tail->next = head->prev = nullptr;
		head->next = tail;
		tail->prev = head;
	};


	~List() noexcept
	{
		auto* deleter = head->next;
		while (deleter && deleter != tail)
		{
			auto* next_deleter = deleter->next;
			delete deleter;
			deleter = next_deleter;
		};
		delete head;
		delete tail;
	}

private:
	template<typename Ty>
	struct node
	{
	public:
		friend class List;
		node* prev = nullptr;
		node* next = nullptr;
		~node()noexcept = default;
		Ty element = Ty();

		node(const Ty& param) { element = param; }
		node(Ty&& param) noexcept
		{
			element = std::forward<Ty>(param);
		}

		node() = default;

		node(node&&) noexcept = default;
		node& operator=(node&&) noexcept = default;

		node(const node&) = default;
		node& operator=(const node&) = default;
	};
	node<Ty>* const head;
	node<Ty>* const tail;
	// 편의함수
	int64_t _size;
	template<typename passTy>
	void inline inserthelper
	(passTy&& param, node<Ty>* lhs, node<Ty>* rhs)noexcept
	{
		auto* inserter = new node<Ty>
			(std::forward<decltype(param)>(param));

		lhs->next = inserter;
		inserter->prev = lhs;

		rhs->prev = inserter;
		inserter->next = rhs;
		_size++;
	};

	inline node<Ty>* nth_node(int64_t offset)const
	{
		auto current = head->next;

		if (offset == 0 && current != tail)return current;

		while (offset-- && current)
			current = current->next;

		if (current == tail)
			return nullptr;


		return current;
	}

	template<typename Ty>
	const node<Ty>* _find_node(const Ty& param) const
	{
		auto* value = head->next;

		while (value->element != param
			&& value != tail)
			value = value->next;

		if (value == nullptr)
			return nullptr;

		return value;
	}
};

template<typename Ty>
inline void List<Ty>::sort() noexcept
{
	int64_t N = size();
	auto& ref = *this;

	for (int32_t i = 0; i < N; i++) {

		for (int32_t j = 0; j < N - (i + 1); j++)
		{
			auto  lhs = ref.nth_node(j);
			auto  rhs = ref.nth_node(j + 1);

			if ((lhs && rhs) == false)   return;

			if (lhs->element > rhs->element) {
				std::swap(lhs->element, rhs->element);
			}
		}
	}
}

template<typename Ty>
inline bool List<Ty>::erase(const Ty& param)
{
	auto* deleter = _find_node(param);

	if (deleter == nullptr)
		return false;

	auto* _prev = deleter->prev;
	auto* _next = deleter->next;
	_prev->next = _next;
	_next->prev = _prev;

	delete deleter;
	_size--;
	return true;
}

template<typename Ty>
inline Ty& List<Ty>::find(const Ty& param)
{
	auto* current = head->next;

	while (current != tail)
	{
		current = current->next;

		if (current->element == param)
			return current->element;
	};
}

template<typename Ty>
inline int64_t List<Ty>::size() const
{
	return _size;
}

template<typename Ty>
std::wostream& operator<<
(std::wostream& out, const List<Ty>& target)
{
	if (target.empty())return out;

	auto* print = target.head->next;

	while (print && print != target.tail)
	{
		//	std::wcout << *print->element << std::endl;
		std::wcout << print->element << std::endl;
		print = print->next;
	};
	return out;
};

