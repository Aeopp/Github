#pragma once
#include <set>
#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <list>
#include <algorithm>
#include <utility>
#include <unordered_map>
#include <xutility>
//using std::rel_ops::operator!=;

template<typename ConTy>
class hash_iterator
{
public:
	friend ConTy;
	using value_type = typename ConTy::value_type;
	using iter_type = typename ConTy::list_iter_type;
	using bucket_type = typename ConTy::table_type; 
	hash_iterator();
	hash_iterator(int64_t idx,
	iter_type list_iter,
	const bucket_type* param_container);


	hash_iterator(hash_iterator&&) noexcept = default;
	hash_iterator& operator=(hash_iterator&&) noexcept = default;
	hash_iterator(const hash_iterator&) = default;
	hash_iterator& operator=(const hash_iterator&) = default;
	/*virtual*/~hash_iterator() = default;

	inline value_type& operator*();
	inline value_type* operator->();
	inline const value_type& operator*()const; 
	inline const value_type* operator->()const; 
	bool operator==(const hash_iterator<ConTy>& rhs)const;
	bool operator!=(const hash_iterator<ConTy>& rhs)const;

    hash_iterator<ConTy>& operator++();
	hash_iterator<ConTy> operator++(int);
	hash_iterator<ConTy>& operator++()const; 
	hash_iterator<ConTy> operator++(int)const; 
private:
	mutable int64_t _cur_idx;
	typename ConTy::list_iter_type  _list_iter;
	const bucket_type* _container = nullptr;

	void increment();
	void increment()const; 
	void decrement(); 
	void decrement()const;
};

template<typename key, typename Ty>
class hash_map
{
public:
	using value_type = std::pair<key,Ty>;
	using hash_type = std::hash<key>;
	using list_type = std::list<value_type>;
	using table_type = std::vector<list_type>;
	using compare_type = std::equal_to<key>;
	using hash_map_type = hash_map<key,Ty>; 
	using list_iter_type =  typename list_type::iterator;
	using hash_iterator_type = typename hash_iterator<hash_map_type>;
private:
	hash_type _hash;
	table_type _table;
	compare_type _compare;
	int64_t _cur_tablesize;
	std::set<int64_t> invalids;
	friend class hash_iterator_type;
public:
	   hash_map(const hash_map&) = default;
	  hash_map(hash_map&&) noexcept = default;
	   hash_map& operator=(hash_map&&) noexcept = default;
	/*virtual */~hash_map() noexcept = default;
	  hash_map(const int64_t table_size); 

	 auto inline begin() const; 
	 auto inline begin();
	 hash_iterator_type inline end() const;
	 hash_iterator_type inline end() ;
	// 템플릿 파라미터 ?? 
	//using Ty = std::wstring;
	//using key = std::wstring;
	/////   //
	hash_map();

	void rehash(const int64_t size)noexcept;

	 void insert(const value_type& param)
	{
		// 재해쉬 해야함 !!
		if (_cur_tablesize > _table.size())
		{
			rehash(_table.size()*2);
		};

		auto& _key = param.first;

		auto Index = gethash(_key);

		// 버킷이 저장되어 있는 인덱스 표시
		invalids.emplace(Index);

		_table[Index].push_front(param);

		++_cur_tablesize;
	};
	 bool erase(const key& _findkey)noexcept
	{
		int64_t Index;

		if (auto [isfind, iter] = findElement(_findkey, Index);
			isfind == false)
		{
			return false;
		}
		else
		{
			_table[Index].erase(iter);
			if (std::empty(_table[Index]))
			{
				std::_Erase_nodes_if(invalids,[&Index]
				(const auto&element) 
				{return element == Index;});
			}
			--_cur_tablesize;
			return true;
		}
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
			return std::pair(true,value_type());
		};
	};
private:
	auto findElement
	(const key& _key,
		int64_t& Index)const
	{
		Index = gethash(_key);
		auto& bucket = _table[Index];
		// 찾은 버킷에서 키가 있는지 체크한다.

		auto isfind = std::find_if(std::begin(bucket),std::end(bucket),
			[&_key,*this](const auto& element)
		{
			return _compare(element.first, _key);
		});

		// 키와 매칭되는 값이 없다 ! 
		if (isfind == std::end(bucket))
		{
			return std::pair(false, (isfind));
		}
		// 값을 찾았다. 
		else
		{
			return std::pair(true, (isfind));
		};
	};
};

template<typename ConTy>
inline hash_iterator<ConTy>::hash_iterator():_cur_idx(-1){};

template<typename ConTy>
inline hash_iterator<ConTy>::hash_iterator(
	int64_t idx,
	iter_type list_iter,
	const bucket_type* param_container)
	:
	_cur_idx(idx), _container(param_container), _list_iter(list_iter)
{};

template<typename ConTy>
inline typename ConTy::value_type& 
hash_iterator<ConTy>::operator*()
{
	return *_list_iter;
};

template<typename ConTy>
inline typename ConTy::value_type*
hash_iterator<ConTy>::operator->()
{
	return static_cast<value_type*>(&(*_list_iter));
};
template<typename ConTy>
inline const typename hash_iterator<ConTy>::
value_type& hash_iterator<ConTy>::operator*() const
{
	return *_list_iter;
};
template<typename ConTy>
inline const typename hash_iterator<ConTy>::
value_type* hash_iterator<ConTy>::operator->() const
{
	return &(*_list_iter);
};
template<typename ConTy>
inline bool hash_iterator<ConTy>::operator==
(const hash_iterator<ConTy>& rhs) const
{
	return  (_container == rhs._container) && (_cur_idx
	==rhs._cur_idx) && (_list_iter == rhs._list_iter);
};

template<typename ConTy>
inline bool hash_iterator<ConTy>::operator!=(const hash_iterator<ConTy>& rhs) const
{
	return (!(*this == rhs));
};

template<typename ConTy>
inline hash_iterator<ConTy>& hash_iterator<ConTy>::operator++()
{
	increment(); 
	return *this; 
};

template<typename ConTy>
inline hash_iterator<ConTy> hash_iterator<ConTy>::operator++(int)
{
	auto return_iter = *this; 
	increment();
	return return_iter; 
}
template<typename ConTy>
inline hash_iterator<ConTy>& hash_iterator<ConTy>::operator++() const
{
	increment();
	return *this;
}
template<typename ConTy>
inline hash_iterator<ConTy> hash_iterator<ConTy>::operator++(int) const
{
	auto return_iter = *this;
	increment();
	return return_iter;
}
;

template<typename ConTy>
inline void hash_iterator<ConTy>::increment()
{
	auto& curtable = (*_container)[_cur_idx];

	++_list_iter;

	if (_list_iter == std::end(curtable))
	{
		while (++_cur_idx < (*_container).size()
			&&(*_container)[_cur_idx].empty() );

		auto non_const_Conty = const_cast<bucket_type*>(_container);

		_list_iter = std::begin((*non_const_Conty)[_cur_idx]);
	};

};

template<typename ConTy>
inline void hash_iterator<ConTy>::increment()const
{
	auto& curtable = (*_container)[_cur_idx];

	++_list_iter;

	if (_list_iter == std::end(curtable))
	{
		while (++_cur_idx < (*_container).size()
			&& (*_container)[_cur_idx].empty());

		_list_iter = std::begin((*_container)[_cur_idx]);
	};

	// 테이블을 가져온다
	// 내부 이터레이터 증가시키기
	// 내부 이터레이터 증가시켰는데 현재테이블 end 가 아니면 종료
	// 내부이터레이터 증가시켰는데 현재테이블 end이면 다음 테이블 가져와서
	// 그 테이블 begin 으로 세팅
	// 테이블 만약 비어있다면 현재인덱스 증가시키며 비어있는 테이블 찾기

	// 테이블을 가져왔는데 테이블이 비어있다면 그 테이블의 begin 으로 세팅
	// 테이블이 비어있지 않다면 _list_iter를 증가시킨다.
	// _list_iter 를 증가시켰는데 end 라면 테이블 인덱스를 증가시키고
	// 그 인덱스의 테이블의 리스트의 begin 으로 세팅

	// 테이블이 비어있다면 begin 을 자신으로 세팅

	// 테이블 인덱스가 max를 초과하면 리턴
};

template<typename ConTy>
inline void hash_iterator<ConTy>::decrement()
{
	if (_list_iter == std::begin(*_container[_cur_idx]))
	{
		while (-- _cur_idx > -1 &&
			std::empty(*_container[_cur_idx]) );

		_list_iter = (std::end(*_container[_cur_idx])-1);
		return;  
	};

	--_list_iter;
};

template<typename ConTy>
inline void hash_iterator<ConTy>::decrement()const
{
	if (_list_iter == std::begin(*_container[_cur_idx]))
	{
		while (--_cur_idx > -1 &&
			std::empty(*_container[_cur_idx]));

		_list_iter = (std::end(*_container[_cur_idx]) - 1);
		return;
	};

	--_list_iter; 
	// 현재테이블 가져오기
	// 현재 테이블 begin 과 이터레이터가 같다면
	// 인덱스 낮춰가면서 비어있지않은 테이블 찾기
	// 비어있지않은 테이블 찾았다면 그 테이블 end-1 에 세팅

	// 현재테이블 begin과 이터레이터가 같지않으면 그냥 빼기
};

template<typename key, typename Ty>
inline  hash_map<key, Ty>::hash_map(const int64_t table_size)
	:
	_table(table_size), _cur_tablesize{ 0 } 
{

};

template<typename key, typename Ty>
inline auto
hash_map<key, Ty>::begin() const
{
	if (invalids.empty()) return hash_iterator_type();

	auto index = *std::begin(invalids);
	auto list_iter = _table[index];

	mutable auto list_iter = std::begin(_table[index]);  
	hash_iterator_type return_iter
	(index, list_iter, &_table);
	return return_iter;

	/*for (int64_t index = 0; index < _table.size(); ++index)
	{
		if (!std::empty(_table[index]))
		{
			hash_iterator_type return_iter
			(index, std::begin(_table[index]), &_table);

			return return_iter;
		}
	};*/
};
template<typename key, typename Ty>
inline auto hash_map<key, Ty>::begin()
{
	if (invalids.empty()) return hash_iterator_type(); 

	auto index= *std::begin(invalids);
	auto list_iter  = _table[index]; 

	hash_iterator_type return_iter
	(index, std::begin(_table[index]), &_table);
	return return_iter; 
	/*for (int64_t index = 0; index < _table.size(); ++index)
	{
		if (!std::empty(_table[index]))
		{
			hash_iterator_type return_iter
			

			return return_iter;
		}
	};*/
};

template<typename key, typename Ty>
inline typename hash_map<key,Ty>::
hash_iterator_type hash_map<key, Ty>::end()const
{
	if (invalids.empty()) return hash_iterator_type();

	auto index = *(--std::end(invalids));
	auto list_iter = _table[index];

	hash_iterator_type return_iter
	(index, (--std::end(_table[index])), &_table);
	return return_iter;
	/*for (int64_t index = _table.size(); -1 < index; --index)
	{
		if (!std::empty(_table[index]))
		{
		return
		hash_iterator_type(index, std::end(_table[index]),&_table);
		}
	};*/
}
template<typename key, typename Ty>
inline typename hash_map<key, Ty>::hash_iterator_type 
hash_map<key, Ty>::end()
{
	if (invalids.empty()) return hash_iterator_type();

	auto index = *(--std::end(invalids));
	auto list_iter = _table[index];

	hash_iterator_type return_iter
	(index, (--std::end(_table[index])), &_table);
	return return_iter;

	/*for (int64_t index = _table.size()-1; -1 < index; --index)
	{
		if (!std::empty(_table[index]))
		{
			return
				hash_iterator_type(index, std::end(_table[index]), &_table);
		}
	};*/
};

template<typename key, typename Ty>
inline hash_map<key, Ty>::hash_map() :hash_map(8)
{};

template<typename key, typename Ty>
inline void hash_map<key, Ty>::rehash(const int64_t size)noexcept
{
	//decltype(*this)change(size); 
	hash_map<key, Ty> change(size); 

	// 리스트의 모든원소를 이동시켜서 다시 삽입(재해쉬)
	auto rehash_inserter=[&change](auto&pair)noexcept
	{
		change.insert(std::move(pair));
	};
	// 유효한 버킷만 리스트를 순회 (원소가 하나라도 들어있는)
	auto rehashfunc=[*this,&change,&rehash_inserter](const auto& invalid_idx)noexcept
	{
		auto& list_ref = _table[invalid_idx]; 

		std::for_each(std::begin(list_ref), 
		std::end(list_ref),rehash_inserter);
	}; 

	decltype(invalids) new_set; 
	new_set.swap(invalids); 

	std::for_each(new_set.begin(),new_set.end(),rehashfunc);

	_table.swap(change._table);
};



