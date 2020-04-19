#pragma once
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <xutility>
#include <initializer_list>
#include <iterator>

//using std::rel_ops::operator!=;
template<typename ConTy>
class hash_const_iterator{

public:
	friend ConTy;
	using value_type = typename const ConTy::value_type;
	using iter_type = typename  ConTy::list_const_iter_type;
	using difference_type = typename ConTy::difference_type;
	using pointer = typename ConTy::const_pointer;
	using iterator_category = std::bidirectional_iterator_tag;;
	using reference = const value_type&;
	using size_type = typename ConTy::size_type; 
	using iterator = typename ConTy::iterator;
	friend iterator; 
	hash_const_iterator() :_cur_idx(-1) {}
	hash_const_iterator(int64_t idx,
		iter_type list_iter,
		const ConTy* param_container)
		:
		_cur_idx(idx), _container(param_container), _list_iter(list_iter)
	{}

	hash_const_iterator(const iterator& rhs)
	{
		_cur_idx = rhs._cur_idx;
		_container = rhs._container;
		_list_iter = rhs._list_iter;
	};
	hash_const_iterator(hash_const_iterator&&) noexcept = default;
	hash_const_iterator& operator=(hash_const_iterator&&) noexcept = default;
	hash_const_iterator(const hash_const_iterator&) = default;
	hash_const_iterator& operator=(const hash_const_iterator&) = default;
	/*virtual*/~hash_const_iterator() = default;

	inline value_type& operator*()const
	{
		return *_list_iter;
	};
	inline value_type* operator->()const 
	{
		return static_cast<value_type*>(&(*_list_iter));
	};
	bool operator==(const hash_const_iterator<ConTy> & rhs)const
	{
		return  (_container == rhs._container) && (_cur_idx
			== rhs._cur_idx) && (_list_iter == rhs._list_iter);
	};
	bool operator!=(const hash_const_iterator<ConTy> & rhs)const
	{
		return (!(*this == rhs));
	};

	hash_const_iterator<ConTy>& operator++()
	{
		increment();
		return *this;
	};
	hash_const_iterator<ConTy> operator++(int) 
	{
		auto return_iter = *this;
		increment();
		return return_iter;
	};
	hash_const_iterator<ConTy>& operator-- () 
	{
		decrement();
		return *this;
	};
	hash_const_iterator<ConTy> operator-- (int) 
	{
		auto return_iterator = *this;
		decrement();
		return return_iterator;
	}
private:
	mutable int64_t _cur_idx;
	typename  iter_type  _list_iter;
	const ConTy* _container = nullptr;

	void increment() 
	{
		auto& curtable = _container->_table;

		auto end_iter = std::end(curtable[_cur_idx]);

		if (_list_iter == end_iter || _list_iter == --end_iter)
		{
			if (auto find_iter = std::find_if(
				std::begin(_container->_invalids), std::end(_container->_invalids),
				[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx < element; });

				find_iter != std::end(_container->_invalids))
			{
				_cur_idx = *find_iter;
				_list_iter = std::begin(curtable[_cur_idx]);
				return;
			}
			else
			{
				*this = _container->end(); 
			}
		}
		else
			++_list_iter;
	};
	void decrement()
	{
		auto& curtable = _container->_table;

		if (_list_iter == std::begin(curtable[_cur_idx]))
		{
			if (auto find_iter = std::find_if(
				std::begin(_container->_invalids), std::end(_container->_invalids),
				[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx > element; });

				find_iter != std::end(_container->_invalids))
			{
				_cur_idx = *find_iter;
				_list_iter = (--std::end(curtable[_cur_idx]));
				return;
			}
			else
			{
				*this = _container->end();
			}
		}
		else
			--_list_iter;
	};
};

template<typename ConTy>
class hash_iterator
{
public:
	friend ConTy;
	using value_type = typename ConTy::value_type;
	using iter_type = typename ConTy::list_iter_type;
	using difference_type = typename ConTy::difference_type;
	using pointer = typename ConTy::pointer;
	using iterator_category = std::bidirectional_iterator_tag;;
	using reference =  value_type&;
	using const_iterator = typename ConTy::const_iterator;
	friend const_iterator; 
	hash_iterator() :_cur_idx(-1) {}
	hash_iterator(int64_t idx,
	iter_type list_iter,
		ConTy* param_container)
		:
		_cur_idx(idx), _container(param_container), _list_iter(list_iter)
	{}

	hash_iterator(hash_iterator&&) noexcept = default;
	hash_iterator& operator=(hash_iterator&&) noexcept = default;
	hash_iterator(const hash_iterator&) = default;
	hash_iterator& operator=(const hash_iterator&) = default;
	/*virtual*/~hash_iterator() = default;

	inline value_type& operator*()
	{
		return *_list_iter;
	};
	inline value_type* operator->()
	{
		return static_cast<value_type*>(&(*_list_iter));
	};

	bool operator==(const hash_iterator<ConTy>& rhs)const
	{
		return  (_container == rhs._container) && (_cur_idx
			== rhs._cur_idx) && (_list_iter == rhs._list_iter);
	};
	bool operator!=(const hash_iterator<ConTy>& rhs)const
	{
		return (!(*this == rhs));
	};

	operator hash_const_iterator<ConTy>()
	{
		return hash_const_iterator<ConTy>
		(_cur_idx, _list_iter, _container);
	}
	
    hash_iterator<ConTy>& operator++()
	{
		increment();
		return *this;
	};
	hash_iterator<ConTy> operator++(int)
	{
		auto return_iter = *this;
		increment();
		return return_iter;
	};
	hash_iterator<ConTy>& operator-- ()
	{
		decrement(); 
		return *this; 
	};
	hash_iterator<ConTy> operator-- (int)
	{
		auto return_iterator = *this; 
		decrement(); 
		return return_iterator; 
	}

private:
	mutable int64_t _cur_idx;
	typename ConTy::list_iter_type  _list_iter;
	ConTy* _container = nullptr;

	void increment()
	{
		auto& curtable = _container->_table;

		auto end_iter = std::end(curtable[_cur_idx]);

		if (_list_iter == end_iter || _list_iter == --end_iter)
		{
			if (auto find_iter = std::find_if(
				std::begin(_container->_invalids), std::end(_container->_invalids),
				[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx < element; });

				find_iter != std::end(_container->_invalids))
			{
				_cur_idx = *find_iter;
				_list_iter = std::begin(curtable[_cur_idx]);
				return;
			}
			else
			{
				*this = _container->end();
			}
		}
		else
			++_list_iter;
	};
	void decrement()
	{
		auto& curtable = _container->_table;

		if (_list_iter == std::begin(curtable[_cur_idx]))
		{
			if (auto find_iter = std::find_if(
				std::begin(_container->_invalids), std::end(_container->_invalids),
				[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx > element; });

				find_iter != std::end(_container->_invalids))
			{
				_cur_idx = *find_iter;
				_list_iter = (--std::end(curtable[_cur_idx]));
				return;
			}
			{
				*this = _container->end();
			}
		}
		else
			--_list_iter;
	};
};

template<typename key, typename Ty>
class hash_map
{
public:
	using key_type = key;
	using mapped_type = Ty;
	using value_type = std::pair<const key,Ty>;
	using value_compare = std::equal_to<Ty>;  
	using hash_type = std::hash<key>;
	using list_type = std::list<value_type>;
	using table_type = std::vector<list_type>;
	using key_compare = std::equal_to<key>;
	using hash_map_type = hash_map<key,Ty>; 
	using size_type = int64_t;
	using difference_type = ptrdiff_t; 
	using pointer = value_type*;
	using const_pointer =  const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using list_iter_type =  typename list_type::iterator;
	using list_const_iter_type = typename list_type::const_iterator;
	using hash_iterator_type = typename hash_iterator<hash_map_type>;

	using iterator = hash_iterator<hash_map_type>;	
	using const_iterator = hash_const_iterator<hash_map_type>;
	/*using reverse_iterator = hash_reverse_iterator<hash_map_type>;*/
	//using const_reverse_iterator = hash_const_reverse_iterator<hash_map_type>;
private:
	hash_type _hash;
	table_type _table;
	key_compare _compare;
	int64_t _cur_tablesize;
	std::set<int64_t> _invalids;
	friend class hash_iterator_type;
	friend class hash_const_iterator<hash_map_type>;
	/*friend class hash_reverse_iterator<hash_map_type>;
	friend class hash_const_reverse_iterator<hash_map_type>;*/
public:
	constexpr hash_map(const hash_map&) = default; 
	constexpr hash_map(hash_map&&) noexcept = default;
	constexpr  hash_map& operator=(hash_map&&) noexcept = default;
	/*virtual */~hash_map() noexcept = default;
	constexpr explicit hash_map(std::initializer_list<value_type>ilist) :
	hash_map(ilist.size())
	{
		insert(std::begin(ilist), std::end(ilist));
	};
hash_map&
operator=(std::initializer_list<value_type>ilist)
	{
			_table.clear();
			_table.shrink_to_fit(); 
			_invalids.clear(); 
			_cur_tablesize = 0; 

			insert(std::begin(ilist), std::end(ilist));
	}
	  hash_map(const int64_t table_size)
		  :
		  _table(table_size), _cur_tablesize{ 0 }
	  {};
	  template<typename InputIterator>
	  hash_map(InputIterator first, InputIterator last,
		 const int64_t table_size=64)
		  :hash_map(table_size)
	  {
		  insert(first, last);
	  }
	/* auto inline begin() const; */
	//
	//template<typename key, typename Ty>
	//inline auto
	//hash_map<key, Ty>::begin() const
	//{
	//	if (_invalids.empty()) return hash_iterator_type();
	//
	//	auto index = *std::begin(_invalids);
	//	auto list_iter = _table[index];
	//
	//	mutable auto list_iter = std::begin(_table[index]);  
	//	hash_iterator_type return_iter
	//	(index, list_iter, &_table);
	//	return return_iter;
	//
	//	/*for (int64_t index = 0; index < _table.size(); ++index)
	//	{
	//		if (!std::empty(_table[index]))
	//		{
	//			hash_iterator_type return_iter
	//			(index, std::begin(_table[index]), &_table);
	//
	//			return return_iter;
	//		}
	//	};*/
	//};
	  iterator inline begin()
	  {
		  if (_invalids.empty()) return iterator();

		  auto index = *std::begin(_invalids);
		  auto list_iter = _table[index];

		  hash_iterator_type return_iter
		  (index, std::begin(_table[index]), this);
		  return return_iter;
	  }
	 /*hash_iterator_type inline end() const;*/
	 //
	 //template<typename key, typename Ty>
	 //inline typename hash_map<key,Ty>::
	 //hash_iterator_type hash_map<key, Ty>::end()const
	 //{
	 //	if (_invalids.empty()) return hash_iterator_type();
	 //
	 //	auto index = *(--std::end(_invalids));
	 //	auto list_iter = _table[index];
	 //
	 //	hash_iterator_type return_iter
	 //	(index, (--std::end(_table[index])), &_table);
	 //	return return_iter;
	 //	/*for (int64_t index = _table.size(); -1 < index; --index)
	 //	{
	 //		if (!std::empty(_table[index]))
	 //		{
	 //		return
	 //		hash_iterator_type(index, std::end(_table[index]),&_table);
	 //		}
	 //	};*/
	 //}
	  iterator inline end()
	  {
		  if (_invalids.empty()) return iterator();

		  auto index = *(--std::end(_invalids));

		  hash_iterator_type return_iter
		  (index, (std::end(_table[index])), this);
		  return return_iter;
	  }
	  
	  const_iterator inline begin()const
	  {
		  if (_invalids.empty()) return const_iterator();

		  auto index = *std::begin(_invalids);
		  auto list_iter = _table[index];

		  const_iterator return_iter
		  (index, std::begin(_table[index]), this);
		  return return_iter;
	  }
	  const_iterator inline cbegin()const
	  {
		  return begin(); 
	  }
	  const_iterator inline end()const
	  {
		  if (_invalids.empty()) return const_iterator();

		  auto index = *(--std::end(_invalids));
		  auto list_iter = _table[index];

		  const_iterator return_iter
		  (index, (std::end(_table[index])), this);
		  return return_iter;
	  }
	  const_iterator inline cend()const
	  {
		  return end(); 
	  }


	// 템플릿 파라미터 ?? 
	//using Ty = std::wstring;
	//using key = std::wstring;
	/////   //
	  hash_map() :hash_map(8)
	  {}

	  void rehash(const int64_t size)noexcept
	  {
		  //decltype(*this)change(size); 
		  hash_map<key, Ty> change(size);

		  // 리스트의 모든원소를 이동시켜서 다시 삽입(재해쉬)
		  auto rehash_inserter = [&change](auto& pair)noexcept
		  {
			  change.insert(std::move(pair));
		  };

		  // 유효한 버킷만 리스트를 순회 (원소가 하나라도 들어있는)

		  auto rehashfunc = [*this, &change, &rehash_inserter](const auto& invalid_idx)noexcept
		  {
			  auto& list_ref = _table[invalid_idx];

			  std::for_each(std::begin(list_ref),
				  std::end(list_ref), rehash_inserter);
		  };
		  std::for_each(_invalids.begin(), _invalids.end(), rehashfunc);

		  _table.swap(change._table);
		  _invalids = std::move_if_noexcept(change._invalids);
	  }
	// void insert(const value_type& param)
	//{
	//	// 재해쉬 해야함 !!
	//	if (_cur_tablesize > _table.size())
	//	{
	//		rehash(_table.size()*2);
	//	};

	//	auto& _key = param.first;

	//	auto Index = gethash(_key);

	//	// 버킷이 저장되어 있는 인덱스 표시
	//	_invalids.emplace(Index);

	//	_table[Index].push_front(param);

	//	++_cur_tablesize;
	//};
	// void insert(value_type&& param)noexcept
	// {
	//	 // 재해쉬 해야함 !!
	//	 if (_cur_tablesize > _table.size())
	//	 {
	//		 rehash(_table.size() * 2);
	//	 };

	//	 auto& _key = param.first;

	//	 auto Index = gethash(_key);

	//	 // 버킷이 저장되어 있는 인덱스 표시
	//	 _invalids.insert(Index);

	//	 _table[Index].emplace_back(std::move(param));

	//	 ++_cur_tablesize;
	// }
	 std::pair<iterator, bool> insert(const value_type& _value)
	 {
		 int64_t Index;
		 const auto& _key = _value.first;

		/* if (auto [isfind, iter] = findElement(_key, Index);
			 isfind == true)
		 {
			 return std::pair(iterator(Index, iter, this), false);
		 }
		 else*/
		 {
			 if (_cur_tablesize > _table.size()) {
				 rehash(_table.size() * 2);
			 };

			 const auto& _key = _value.first;

			 auto Index = gethash(_key);
			 _invalids.insert(Index);
			 auto list_iter = std::begin(_table[Index]);
			 auto ret_iter = _table[Index].insert(list_iter, _value);
			 ++_cur_tablesize;

			 return std::pair(iterator(Index, ret_iter, this), true);
		 };
	 };
	/* std::pair<iterator, bool> insert( value_type&& _value)
	 {
		 int64_t Index;
		  auto _key = _value.first;

		 if (auto [isfind, iter] = findElement(_key, Index);
			 isfind == true)
		 {
			 iterator iter(Index, iter, this);
			 return std::make_pair(iter, false);
		 }
		 else
		 {
			 if (_cur_tablesize > _table.size()) {
				 rehash(_table.size() * 2);
			 };

			 const auto& _key = _value.first;

			 auto Index = gethash(_key);
			 _invalids.insert(Index);
			 auto list_iter = std::begin(_table[Index]);
			 auto ret_iter = _table[Index].insert(list_iter,std::move( _value));
			 ++_cur_tablesize;

			 return std::pair(iterator(_key, ret_iter, this), true);
		 };
	 };*/

	 // copy move
	 // 11
	 size_type erase(const key& _findkey)noexcept
	{
		int64_t Index;

		if (auto [isfind, iter] = findElement(_findkey, Index);
			isfind == false)
		{
			return 0;
		}
		else
		{
			_table[Index].erase(iter);
			if (std::empty(_table[Index]))
			{
				_invalids.erase(Index);
			}
			--_cur_tablesize;
			return 1;
		}
	};
	 iterator erase(iterator pos)noexcept
	 {
		 auto del_pos = pos;
		 auto delete_idx = del_pos._cur_idx;

		  --_cur_tablesize;
		  if (std::empty(_table[delete_idx]))
		  {
			  _invalids.erase(delete_idx);
		  }
		 
		//  std::remove_reference_t<iterator> ret_iter = ++pos;
		 _table[delete_idx].erase(del_pos._list_iter);
		 return ++pos; 
	 };
	 iterator erase(iterator first ,iterator end)noexcept
	 {
		 while (first != end)
		 {
			first =erase(first);
		 };
		 return end;
	 };
	auto inline gethash(const key& _key)const
	{
		return _hash(_key) % _table.size();
	};
	auto find(const key& _key)const
	{
		int64_t Index;

		if (auto [isfind, iter] = findElement(_key, Index);
			isfind == true)
		{
			return std::pair(true, *iter);
		}
		else
		{
			return std::pair(false,value_type());
		};
	};
	 constexpr bool empty()const
	 {
		 return _invalids.empty();
	 };
	 constexpr size_type size()const
	 {
		 return _invalids.size();
	 };
	 constexpr size_type max_size()const
	 {
		 return _table[0].max_size(); 
	 };

	 Ty& operator[](const key_type& _key) 
	 {
		 int64_t index;

		 if (auto [isfind, iter] = findElement(_key, index);
			 isfind == true)
		 {
			 return *iter.second;
		 }
		 else
		 {
			 insert(std::pair(_key,Ty())); 
		 }
	 }; 
	 template<typename _valty,
		 typename = std::enable_if_t<std::is_constructible_v<value_type, _valty>>>
		 iterator insert(iterator pos,_valty&& value)
	 {
		 return insert(std::forward<_valty>(value)).first;
	 };
	 template<typename InputIterator> 
	constexpr void insert(InputIterator first, InputIterator last)
	 {
		 /* while (first != last)
		  {
			  insert(*first);
			  ++first;
		  }*/
		auto inserter = std::insert_iterator(*this,this->begin());
		std::copy(first, last, inserter);
	 };
	constexpr void insert(std::initializer_list<value_type> ilist)
	{
	auto inserter = std::insert_iterator(*this, begin());
	std::copy(std::begin(ilist), std::end(ilist) , inserter);
	};
	
	std::pair<iterator,bool> emplace(value_type&& _value)noexcept
	{
		int64_t Index;
		const auto& _key = _value.first;

		if (auto [isfind, iter] = findElement(_key, Index);
			isfind == true)
		{
			return std::pair(iterator(_key, iter, this), false);
		}
		else
		{
			if (_cur_tablesize > _table.size()){
				rehash(_table.size() * 2);
			};

			const auto& _key = _value.first;

			auto Index = gethash(_key);
			_invalids.insert(Index);
			auto list_iter = std::begin(_table[Index]);
			auto ret_iter = _table[Index].insert(list_iter,std::move(_value));
			++_cur_tablesize;

			return std::pair(iterator(_key,ret_iter,this), true);
		};
	}
	iterator emplace_hint(iterator hint/*ignore hint*/
		, value_type&& _value)noexcept
	{
		return emplace(_value).first;
	};

	void swap(hash_map_type& hashIn)noexcept
	{
		std::swap(_table, hashIn._table);
		std::swap(_invalids, hashIn._invalids);
		std::swap(_cur_tablesize, hashIn._cur_tablesize);
		std::swap(_compare, hashIn._compare);
		std::swap(_hash, hashIn._hash);
	};
	void clear() noexcept
	{
		_invalids.clear();
		_cur_tablesize = 0;
		for (auto & bucket : _table)
		{
			bucket.clear(); 
		}
	}

	key_compare key_comp() const
	{
		return _compare; 
	}
	value_compare value_comp() const
	{
		return value_compare();
	};
	iterator find(const key_type& _key)
	{
		int64_t index;

		if (auto [isfind, iter] =
			const_cast<decltype(this)>(this)->findElement(_key, index);
			isfind == true)
		{
			return iterator(index, iter, this);
		}
		else
		{
			return end();
		}
	}
	/*const_iterator find(const key_type& _key)const
	{
		const_iterator _iter = const_cast<decltype(this)>(this)->find(_key);
	};*/
	constexpr inline size_type count(const key_type& _key) const
	{
		int64_t index = gethash(_key);
		auto&cur_table = _table[index];
		if (cur_table.empty())return 0; 

		auto diff_size = 
		std::count_if(std::begin(cur_table), std::end(cur_table),
		[_key = _key](const auto& element) { return _key == element;  });

		return diff_size; 
	}
	std::pair<iterator, iterator> equal_range(const key_type& _key)
	{
		int64_t index= gethash(_key);
		auto& cur_list = _table[index]; 
		if (cur_list.empty()) return std::pair(end(), end());

		cur_list.sort();
		auto&& [left, right] =
			std::equal_range(std::begin(cur_list), std::end(cur_list),
				std::pair(_key, Ty()),
				[](const auto& lhs, const auto& rhs)
				{return lhs.first < rhs.first;  });

		auto right_index = index;
		if (right == std::end(cur_list))
		{
			if (auto find_next_index =next_index(right_index);

				find_next_index!=std::end(_invalids)  ) 
			{
				right_index = *find_next_index;
				right = _table[right_index].begin();
			}
			else
			{

			}
		}
		auto&& ret_left = iterator(index, std::move(left), this);
		auto&& ret_right = iterator(right_index, std::move(right), this);
		return std::pair(ret_left, ret_right); 
	};
	std::pair<const_iterator, const_iterator> equal_range(const key_type& _key)
	const
	{
		auto&&[left,right] = 
		const_cast<decltype(this)>(this)->equal_range(_key);

		const_iterator&& ret_left = left;
		const_iterator&& ret_right = right;

		return std::pair(ret_left, ret_right); 
	};
private:
	std::pair<bool,list_iter_type> findElement
	(const key& _key,
		int64_t& Index)const
	{
		Index = gethash(_key);
		auto& bucket = _table[Index];

		auto isfind = std::find_if(std::begin(bucket),std::end(bucket),
			[&_key,*this](const auto& element)
		{
			return _compare(element.first, _key);
		});

		if (isfind == std::end(bucket))
		{
			return std::pair(false, (isfind));
		}
		else
		{
			return std::pair(true, (isfind));
		};
	};
	auto findElement
	(const key& _key,
		int64_t& Index)
	{
		Index = gethash(_key);
		auto& bucket = _table[Index];

		auto isfind = std::find_if(std::begin(bucket), std::end(bucket),
			[&_key, *this](const auto& element)
		{
			return _compare(element.first, _key);
		});

		if (isfind == std::end(bucket))
		{
			return std::pair(false, (isfind));
		}
		else
		{
			return std::pair(true, (isfind));
		};
	};
	constexpr auto next_index(const int64_t cur_index)noexcept 
	{
		return std::find_if(std::begin(_invalids), std::end(_invalids),
			[cur_index = cur_index](const auto& element)
			{return cur_index < element;  });
	}
};


