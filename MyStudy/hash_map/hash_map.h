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
	hash_iterator();
	hash_iterator(int64_t idx,
	iter_type list_iter,
	ConTy* param_container);


	hash_iterator(hash_iterator&&) noexcept = default;
	hash_iterator& operator=(hash_iterator&&) noexcept = default;
	hash_iterator(const hash_iterator&) = default;
	hash_iterator& operator=(const hash_iterator&) = default;
	/*virtual*/~hash_iterator() = default;

	inline value_type& operator*();
	inline value_type* operator->();
//	inline const value_type& operator*(); 
//	inline const value_type* operator->(); 
	bool operator==(const hash_iterator<ConTy>& rhs)const;
	bool operator!=(const hash_iterator<ConTy>& rhs)const;

    hash_iterator<ConTy>& operator++();
	hash_iterator<ConTy> operator++(int);
// 	hash_iterator<ConTy>& operator++()const; 
// 	hash_iterator<ConTy> operator++(int)const; 
private:
	mutable int64_t _cur_idx;
	typename ConTy::list_iter_type  _list_iter;
	ConTy* _container = nullptr;

	void increment();
	//void increment()const; 
	void decrement(); 
	//void decrement()const;
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

	/* auto inline begin() const; */
	 auto inline begin();
	 /*hash_iterator_type inline end() const;*/
	 auto inline end() ;
	// ���ø� �Ķ���� ?? 
	//using Ty = std::wstring;
	//using key = std::wstring;
	/////   //
	hash_map();

	void rehash(const int64_t size)noexcept;

	 void insert(const value_type& param)
	{
		// ���ؽ� �ؾ��� !!
		if (_cur_tablesize > _table.size())
		{
			rehash(_table.size()*2);
		};

		auto& _key = param.first;

		auto Index = gethash(_key);

		// ��Ŷ�� ����Ǿ� �ִ� �ε��� ǥ��
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
				invalids.erase(Index);
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
		// ã�� ��Ŷ���� Ű�� �ִ��� üũ�Ѵ�.

		auto isfind = std::find_if(std::begin(bucket),std::end(bucket),
			[&_key,*this](const auto& element)
		{
			return _compare(element.first, _key);
		});

		// Ű�� ��Ī�Ǵ� ���� ���� ! 
		if (isfind == std::end(bucket))
		{
			return std::pair(false, (isfind));
		}
		// ���� ã�Ҵ�. 
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
	ConTy* param_container)
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
//template<typename ConTy>
//inline const typename hash_iterator<ConTy>::
//value_type& hash_iterator<ConTy>::operator*() const
//{
//	return *_list_iter;
//};
//template<typename ConTy>
//inline const typename hash_iterator<ConTy>::
//value_type* hash_iterator<ConTy>::operator->() const
//{
//	return &(*_list_iter);
//};
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
//template<typename ConTy>
//inline hash_iterator<ConTy>& hash_iterator<ConTy>::operator++() const
//{
//	increment();
//	return *this;
//}
//template<typename ConTy>
//inline hash_iterator<ConTy> hash_iterator<ConTy>::operator++(int) const
//{
//	auto return_iter = *this;
//	increment();
//	return return_iter;
//};
template<typename ConTy>
inline void hash_iterator<ConTy>::increment()
{
	auto& curtable = _container->_table; 

	++_list_iter;

	if (_list_iter == std::end(curtable[_cur_idx]))
	{
		if (auto find_iter = std::find_if(
			std::begin(_container->invalids), std::end(_container->invalids),
			[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx  < element; });

			find_iter != std::end(_container->invalids) )
		{
			_cur_idx = *find_iter;
			_list_iter = std::begin(curtable[_cur_idx]);
		};
		//

		//while (++_cur_idx < curtable.size()
		//	&&(*_container)[_cur_idx].empty() );

		//auto non_const_Conty = const_cast<Conty_type*>(_container);

		//_list_iter = std::begin((*non_const_Conty)[_cur_idx]);
	};
};
//
//template<typename ConTy>
//inline void hash_iterator<ConTy>::increment()const
//{
//	auto& curtable = (*_container)[_cur_idx];
//
//	++_list_iter;
//
//	if (_list_iter == std::end(curtable))
//	{
//		while (++_cur_idx < (*_container).size()
//			&& (*_container)[_cur_idx].empty());
//
//		_list_iter = std::begin((*_container)[_cur_idx]);
//	};
//
//	// ���̺��� �����´�
//	// ���� ���ͷ����� ������Ű��
//	// ���� ���ͷ����� �������״µ� �������̺� end �� �ƴϸ� ����
//	// �������ͷ����� �������״µ� �������̺� end�̸� ���� ���̺� �����ͼ�
//	// �� ���̺� begin ���� ����
//	// ���̺� ���� ����ִٸ� �����ε��� ������Ű�� ����ִ� ���̺� ã��
//
//	// ���̺��� �����Դµ� ���̺��� ����ִٸ� �� ���̺��� begin ���� ����
//	// ���̺��� ������� �ʴٸ� _list_iter�� ������Ų��.
//	// _list_iter �� �������״µ� end ��� ���̺� �ε����� ������Ű��
//	// �� �ε����� ���̺��� ����Ʈ�� begin ���� ����
//
//	// ���̺��� ����ִٸ� begin �� �ڽ����� ����
//
//	// ���̺� �ε����� max�� �ʰ��ϸ� ����
//};

template<typename ConTy>
inline void hash_iterator<ConTy>::decrement()
{	
	auto& curtable = _container->_table; 

	if (_list_iter == std::begin(curtable[_cur_idx]))
	{
		if (auto find_iter = std::find_if(
			std::begin(_container->invalids), std::end(_container->invalids),
			[_cur_idx = this->_cur_idx](const auto& element) {return _cur_idx > element; });

			find_iter != std::end(_container->invalids))
		{
			_cur_idx = *find_iter;
			_list_iter = (--std::end(curtable[_cur_idx]));
			return;
		};

		/*while (-- _cur_idx > -1 &&
			std::empty(*_container[_cur_idx]) );

		*/


		//_list_iter = (std::end(*_container[_cur_idx])-1);
		//return;  
	}else
		--_list_iter;
};
//
//template<typename ConTy>
//inline void hash_iterator<ConTy>::decrement()const
//{
//	if (_list_iter == std::begin(*_container[_cur_idx]))
//	{
//		while (--_cur_idx > -1 &&
//			std::empty(*_container[_cur_idx]));
//
//		_list_iter = (std::end(*_container[_cur_idx]) - 1);
//		return;
//	};
//
//	--_list_iter; 
//	// �������̺� ��������
//	// ���� ���̺� begin �� ���ͷ����Ͱ� ���ٸ�
//	// �ε��� ���簡�鼭 ����������� ���̺� ã��
//	// ����������� ���̺� ã�Ҵٸ� �� ���̺� end-1 �� ����
//
//	// �������̺� begin�� ���ͷ����Ͱ� ���������� �׳� ����
//};

template<typename key, typename Ty>
inline  hash_map<key, Ty>::hash_map(const int64_t table_size)
	:
	_table(table_size), _cur_tablesize{ 0 } 
{

};
//
//template<typename key, typename Ty>
//inline auto
//hash_map<key, Ty>::begin() const
//{
//	if (invalids.empty()) return hash_iterator_type();
//
//	auto index = *std::begin(invalids);
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
template<typename key, typename Ty>
inline auto hash_map<key, Ty>::begin()
{
	if (invalids.empty()) return hash_iterator_type(); 

	auto index= *std::begin(invalids);
	auto list_iter  = _table[index]; 

	hash_iterator_type return_iter
	(index, std::begin(_table[index]),this);
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
//
//template<typename key, typename Ty>
//inline typename hash_map<key,Ty>::
//hash_iterator_type hash_map<key, Ty>::end()const
//{
//	if (invalids.empty()) return hash_iterator_type();
//
//	auto index = *(--std::end(invalids));
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
template<typename key, typename Ty>
inline auto 
hash_map<key, Ty>::end()
{
	if (invalids.empty()) return hash_iterator_type();

	auto index = *(--std::end(invalids));
	auto list_iter = _table[index];

	hash_iterator_type return_iter
	(index, (std::end(_table[index])), this);
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
	 
	// ����Ʈ�� �����Ҹ� �̵����Ѽ� �ٽ� ����(���ؽ�)
	auto rehash_inserter=[&change](auto&pair)noexcept
	{
		change.insert(std::move(pair));
	};

	// ��ȿ�� ��Ŷ�� ����Ʈ�� ��ȸ (���Ұ� �ϳ��� ����ִ�)

	auto rehashfunc=[*this,&change,&rehash_inserter](const auto& invalid_idx)noexcept
	{
		auto& list_ref = _table[invalid_idx]; 

		std::for_each(std::begin(list_ref), 
		std::end(list_ref),rehash_inserter);
	}; 
	std::for_each(invalids.begin(), invalids.end(),rehashfunc);

	_table.swap(change._table);
	invalids = std::move_if_noexcept(change.invalids); 
};



