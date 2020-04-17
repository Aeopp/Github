#pragma once
#include "const_hash_map_iterator.h"
#include <iterator>

template<typename HashMap>
class hash_map_iterator :public const_hash_map_iterator<HashMap> 
{
public :
	
	using Super = const_hash_map_iterator<HashMap>;

	explicit hash_map_iterator(const hash_map_iterator&) = default;
	hash_map_iterator&operator=(const hash_map_iterator&) = default;
	hash_map_iterator&operator=(hash_map_iterator&&)noexcept = default;
	explicit hash_map_iterator(hash_map_iterator&&)noexcept = default;

	using value_type = typename const_hash_map_iterator<HashMap>::value_type;
	using list_iterator_type = typename HashMap::ListType::iterator;
	
	hash_map_iterator() noexcept = default;
	hash_map_iterator(uint64_t bucket, list_iterator_type listIt,HashMap* inHashMap);

	value_type& operator*();
	value_type* operator->();

	hash_map_iterator<HashMap>& operator++();
	hash_map_iterator<HashMap>operator++(int);
	hash_map_iterator<HashMap>&operator--();
	hash_map_iterator<HashMap>operator--(int);
};

template<typename HashMap>
inline hash_map_iterator<HashMap>::hash_map_iterator(uint64_t bucket, list_iterator_type listIt, HashMap* inHashMap)
	:Super(bucket,listIt,inHashMap) {}

template<typename HashMap>
inline typename hash_map_iterator<HashMap>::
value_type& hash_map_iterator<HashMap>::operator*()
{
	return const_cast<value_type&>(*this->mListIterator);
};

template<typename HashMap>
inline typename hash_map_iterator<HashMap>::value_type* 
hash_map_iterator<HashMap>::operator->()
{
	return const_cast<value_type*>(&(*this->mListIterator));
};

template<typename HashMap>
inline hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator++()
{
	Super::increment();
	return *this;
}

template<typename HashMap>
inline hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator++(int)
{
	auto RetVal = *this;
	Super::increment();
	return RetVal;
}

template<typename HashMap>
inline hash_map_iterator<HashMap>& hash_map_iterator<HashMap>::operator--()
{
	Super::decrement();
	return *this;
}

template<typename HashMap>
inline hash_map_iterator<HashMap> hash_map_iterator<HashMap>::operator--(int)
{
	auto* OldValue = *this;
	Super::decrement();
	return OldValue; 
}
