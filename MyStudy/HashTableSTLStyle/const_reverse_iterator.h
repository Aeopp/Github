#include <xutility>
#pragma once
#include "const_hash_map_iterator.h"

template<typename HashMap>
class const_reverse_hash_map_iterator : public const_hash_map_iterator<HashMap>
{
	using Super = const_hash_map_iterator<HashMap>;
	using value_type = typename HashMap::value_type;
	using pointer = typename HashMap::value_type*;
	using reference = typename HashMap::value_type&;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;
	using list_iterator_type = typename HashMap::ListType::reverse_iterator;

	explicit const_reverse_hash_map_iterator(const const_reverse_hash_map_iterator&) = default;
	const_reverse_hash_map_iterator& operator=(const const_reverse_hash_map_iterator&) = default;
	const_reverse_hash_map_iterator& operator=(const_reverse_hash_map_iterator&&)noexcept = default;
	explicit const_reverse_hash_map_iterator(const_reverse_hash_map_iterator&&)noexcept = default;

	const_reverse_hash_map_iterator() noexcept = default;
	const_reverse_hash_map_iterator(uint64_t bucket,
	list_iterator_type listIt, HashMap* inHashMap);

	value_type& operator*();
	value_type* operator->();

	hash_map_iterator<HashMap>& operator++();
	hash_map_iterator<HashMap>operator++(int);
	hash_map_iterator<HashMap>& operator--();
	hash_map_iterator<HashMap>operator--(int);
};

template<typename HashMap>
inline const_reverse_hash_map_iterator<HashMap>::const_reverse_hash_map_iterator
(uint64_t bucket, list_iterator_type listIt, HashMap* inHashMap)
	:this->mBuckets(bucket), this->mListIterator(listIt), this->HashMap(inHashMap)
{}

template<typename HashMap>
inline typename HashMap::value_type& const_reverse_hash_map_iterator<HashMap>::operator*()
{
	return *(this->mListIterator);
}

template<typename HashMap>
inline typename HashMap::value_type* const_reverse_hash_map_iterator<HashMap>::operator->()
{
	return &(*(this->mListIterator));
}
template<typename HashMap>
inline hash_map_iterator<HashMap>& const_reverse_hash_map_iterator<HashMap>::operator++()
{
	
}

template<typename HashMap>
inline hash_map_iterator<HashMap> const_reverse_hash_map_iterator<HashMap>::operator++(int)
{
	return hash_map_iterator<HashMap>();
}

template<typename HashMap>
inline hash_map_iterator<HashMap>& const_reverse_hash_map_iterator<HashMap>::operator--()
{
	
}

template<typename HashMap>
inline hash_map_iterator<HashMap> const_reverse_hash_map_iterator<HashMap>::operator--(int)
{
	return hash_map_iterator<HashMap>();
}
