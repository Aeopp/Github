#pragma once
#include <iostream>
#include <xutility>
#include "hash_map.h"
template<typename HashMap>
class const_hash_map_iterator 
{
public:
	using list_iterator_type = 
	typename HashMap::ListType::const_iterator;

	using value_type = typename HashMap::value_type;
	using pointer = typename HashMap::value_type*;
	using reference = typename HashMap::value_type&;
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;

	const_hash_map_iterator(uint64_t bucket,
	list_iterator_type listIt,const HashMap* inHashmap);

	const value_type& operator*() const;
	const value_type* operator->()const;

	const_hash_map_iterator<HashMap>& operator++();
	const_hash_map_iterator<HashMap> operator++(int);

	const_hash_map_iterator<HashMap>& operator--();
	const_hash_map_iterator<HashMap>operator--(int);

	const_hash_map_iterator<HashMap>();

	const_hash_map_iterator<HashMap>
	(const const_hash_map_iterator<HashMap>&) = default; 

	const_hash_map_iterator<HashMap>& operator=
	(const const_hash_map_iterator<HashMap>&) = default;

	const_hash_map_iterator<HashMap>& operator=
	(const_hash_map_iterator<HashMap>&&) noexcept= default;

	const_hash_map_iterator<HashMap>
	(const_hash_map_iterator<HashMap>&&) noexcept = default;

	bool operator==(const const_hash_map_iterator<HashMap>& rhs)const;
	bool operator!=(const const_hash_map_iterator<HashMap>& rhs)const;
	virtual ~const_hash_map_iterator() = default; 

	protected:
	uint64_t mBucketIndex;
	list_iterator_type mListIterator;
	const HashMap* mHashmap;
	void increment();
	void decrement();
};

template<typename HashMap>
inline const_hash_map_iterator<HashMap>::const_hash_map_iterator()
	:
	mBucketIndex(uint64_t(0)), mListIterator(list_iterator_type()), mHashmap(nullptr) {}

template<typename HashMap>
inline  const_hash_map_iterator<HashMap>::const_hash_map_iterator
(uint64_t bucket, list_iterator_type listIt, const HashMap* inHashmap)
	:mBucketIndex(bucket), mListIterator(listIt), mHashmap(inHashmap){}

template<typename HashMap>
inline const typename
HashMap::value_type& const_hash_map_iterator<HashMap>::operator*() const
{
	return *mListIterator;
}

template<typename HashMap>
const typename
HashMap::value_type*
const_hash_map_iterator<HashMap>::operator->() const
{
	return &(*mListIterator);
};
template<typename HashMap>
const_hash_map_iterator<HashMap>&
const_hash_map_iterator<HashMap>::operator++()
{
	increment();
	return *this;
}

template<typename HashMap>
const_hash_map_iterator<HashMap>
const_hash_map_iterator<HashMap>::operator++(int)
{
	auto RetVal = *this;
	increment();
	return RetVal;
}

template<typename HashMap>
const_hash_map_iterator<HashMap>&
const_hash_map_iterator<HashMap>::operator--()
{
	decrement();
	return *this;
}

template<typename HashMap>
const_hash_map_iterator<HashMap>
const_hash_map_iterator<HashMap>::operator--(int)
{
	auto RetVal = *this;
	decrement();
	return RetVal;
}

template<typename HashMap>
bool const_hash_map_iterator<HashMap>::operator==
(const const_hash_map_iterator<HashMap>& rhs) const
{
	return (mHashmap == rhs.mHashmap &&
		mBucketIndex == rhs.mBucketIndex &&
		mListIterator == rhs.mListIterator);
}

template<typename HashMap>
bool const_hash_map_iterator<HashMap>::operator!=
(const const_hash_map_iterator<HashMap>& rhs) const
{
	return !(*this == rhs);
};

template<typename HashMap>
void const_hash_map_iterator<HashMap>::increment()
{
	++mListIterator;

	auto& buckets = mHashmap->mBuckets;

	if (mListIterator == std::end(buckets[mBucketIndex]))
	{
		for (uint64_t i = mBucketIndex + 1; i < buckets.size(); ++i)
		{
			if (!buckets[i].empty())
			{
				mListIterator = std::begin(buckets[i]);
				mBucketIndex = i;
				return;
			}
		}
	};

	mBucketIndex = buckets.size() - 1;
	mListIterator = std::end(buckets[mBucketIndex]);
}

template<typename HashMap>
void const_hash_map_iterator<HashMap>::decrement()
{
	auto& buckets = mHashmap->mBuckets;

	if (mListIterator == std::begin(buckets[mBucketIndex]))
	{
		for (int32_t i = mBucketIndex - 1; i >= 0; --i)
		{
			if (!buckets[i].empty())
			{
				mListIterator = std::end(buckets[i]);
				--mListIterator;
				mBucketIndex = i;
				return;
			}
		}
		mBucketIndex = buckets.size() - 1;
		mListIterator = std::end(buckets[mBucketIndex]);
	}
	else
	{
		--mListIterator;
	}
}


