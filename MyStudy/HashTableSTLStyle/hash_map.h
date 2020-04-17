#pragma once
#include <vector>
#include <list>
#include <utility>
#include <iterator>
#include "Hash.h"
#include "hash_map_iterator.h"

template<typename Key,typename T,
typename compare= std::equal_to<Key>,
typename Hash = Hash<Key>>
class HashMap
{
public:
	using key_type = Key;
	using mapped_type = T;
	using value_type = std::pair<const Key, T>;
	using ListType = std::list<value_type>;
	using key_compare = compare;
	using reference = std::pair<const Key, T>&;
	using const_reference = const std::pair<const Key, T>&;
	using size_type = uint64_t;
	using difference_type = ptrdiff_t;
	using hash_map_type = HashMap<Key, T, compare, Hash>; 

	using iterator =   hash_map_iterator<hash_map_type>;
	using const_iterator = const_hash_map_iterator<hash_map_type>;

	using reverse_iterator = hash_map_iterator<hash_map_type>;
	using const_reverse_iterator = const_hash_map_iterator<hash_map_type>;

	class value_compare :
		public std::binary_function<typename value_type, typename value_type,bool>
	{
	public:
		bool operator()(const value_type& x, const value_type& y)const 
		{
			return comp(x.first, y.first); 
		}
	protected:
		compare comp;
		value_compare(compare c) :comp(c) {};
	};

	friend class hash_map_iterator<hash_map_type>	   ;
	
	template<typename InputIterator>
	HashMap(InputIterator first, InputIterator last,
	const compare& comp = compare(),
	uint64_t numBuckets = 101, const Hash& hash = Hash());

	explicit HashMap(std::initializer_list<value_type> il, const compare& comp = compare(),
	uint64_t numBuckets = 10, const Hash& hash = Hash());

	hash_map_type& operator=(std::initializer_list<value_type> il);


	iterator begin();
	iterator end();
	const_iterator begin()const;
	const_iterator end() const;
	const_iterator cbegin()const;
	const_iterator cend()const; 

	virtual ~HashMap()noexcept = default;

	HashMap& operator=(HashMap&&) noexcept= delete;
	HashMap& operator=(const HashMap&) = delete;

	explicit HashMap(HashMap&&) noexcept = delete;
	explicit HashMap(const HashMap&) = delete;

	explicit HashMap(const compare& comp = compare(),
	uint64_t numBuckets = 101, const Hash& hash = Hash());

	void insert(const value_type& x)noexcept;
	
	value_type* find(const key_type& k);
	const value_type* find(const key_type& k)const;
	
	T& operator[](const key_type& k);
	bool empty()const;
	size_type size()const;
	size_type max_size()const;

	void swap(hash_map_type& hashIn);



	std::pair<iterator, bool> insert(const value_type& x)
	{
		uint64_t bucket;
		auto it = findElement(x.first, bucket);
		bool inserted = false;

		if (it == std::end(this->mBuckets[bucket]))
		{
			it = mBuckets[bucket].insert(std::end(mBuckets[bucket]), x);
			inserted = true;
			mSize++;
		};
		return pair(hash_map_iterator<hash_map_type>(bucket, it, this), inserted);
	};



	iterator insert(iterator position, const value_type& x);
	template <typename InputIterator>
	void insert(InputIterator first, InputIterator last);

	std::pair<iterator,bool>emplace(value_type&& x);
	iterator emplace_hint(iterator hint, value_type&& x);


	uint64_t erase(const key_type& x);
	iterator erase(iterator position);
	iterator erase(iterator first, iterator last); 

	
	void clear()noexcept;

	key_compare key_comp() const;
	value_compare value_comp() const;

	iterator find(const key_type& x);
	const_iterator find(const key_type& x)const;

	std::pair<iterator, iterator> 
	equal_range(const key_type& x);

	const std::pair<const_iterator,const_iterator> 
	equal_range(const key_type& x)const; 

	uint64_t count(const key_type& x)const;


	
	typename HashMap<Key, T, compare, Hash>::ListType::iterator findElement
	(const key_type& k,
	uint64_t& bucket)
	{
		bucket = mHash(k) % mBuckets.size();

		for (auto it = std::begin(mBuckets[bucket]);
			it != std::end(mBuckets[bucket]); ++it)
		{
			if (mComp(it->first, k))
			{
				return it;
			}
		};
		return std::end(mBuckets[bucket]);
	};
	
	friend class hash_map_iterator<hash_map_type>; 
	friend class const_hash_map_iterator<hash_map_type>;
private:
	std::vector<ListType> mBuckets;
	size_t mSize;
	compare mComp;
	Hash mHash; 
};

template<typename Key, typename T, typename compare, typename Hash>
inline HashMap<Key, T, compare, Hash>::HashMap
(std::initializer_list<value_type> il, const compare& comp, 
uint64_t numBuckets, const Hash& hash)
{
	if (numBuckets == 0)
	{throw std::invalid_argument("Number of buckets must be positive");}

	mBuckets.resize(numBuckets);
	insert(std::begin(il), std::end(il));
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::
hash_map_type& HashMap<Key, T, compare, Hash>::
operator=(std::initializer_list<value_type> il)
{
	this->clear();
	insert(std::begin(il), std::end(il));
	return *this; 
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare,
Hash>::iterator HashMap<Key, T, compare, Hash>::begin()
{
	if (mSize == 0)
	{
		return end();
	}

	for (uint64_t i = 0; i < mBuckets.size(); ++i)
	{
		if (!mBuckets[i].empty())
		{
			return hash_map_iterator<hash_map_type>(i, std::begin(mBuckets[i]), this);
		}
	}

	return end();
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::iterator HashMap
<Key, T, compare, Hash>::end()
{
	// Hash Map 의 종료 반복자는 마지막 버킷 리스트이 종료 반복자와 같다.
	uint64_t bucket = mBuckets.size() - 1;

	return hash_map_iterator<hash_map_type>
		(bucket, std::end(mBuckets[bucket]), this);
};

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::
const_iterator HashMap<Key, T, compare, Hash>::begin() const
{
	return const_cast< hash_map_type*>(this)->begin();
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>
::const_iterator HashMap<Key, T, compare, Hash>::end() const
{
	return const_cast< hash_map_type*>(this)->end();
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::
const_iterator HashMap<Key, T, compare, Hash>::cbegin() const
{
	return this->begin();
};

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::const_iterator 
HashMap<Key, T, compare, Hash>::cend() const
{
	return this->end();
};

template<typename Key, typename T, typename compare, typename Hash>
inline HashMap<Key, T, compare, Hash>::HashMap(const compare& comp, uint64_t numBuckets, const Hash& hash)
	:mSize(0), mComp(comp), mHash(hash)
{
	if (numBuckets == 0)
	{
		throw std::invalid_argument("Number of buckets must be positive");
	};
	mBuckets.resize(numBuckets);
};



template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>
::iterator HashMap<Key, T, compare, Hash>::
insert(iterator position/*무시*/, const value_type& x)
{
	return insert(x).first;
}

template<typename Key, typename T, typename compare, typename Hash>
inline std::pair<typename HashMap<Key, T, compare, Hash>::iterator, bool> 
HashMap<Key, T, compare, Hash>::emplace(value_type&& x)
{
	uint64_t bucket;
	auto it = findElement(x.first, bucket);
	bool inserted = false;

	if (it == std::end(mBuckets[bucket]))
	{
		it = mBuckets[bucket].emplace(std::end(mBuckets[bucket]), x);
		inserted = true;
		mSize++;  
	}

	return std::make_pair(hash_map_iterator<hash_map_type>
	(bucket, it, this), inserted); 
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::iterator HashMap<Key, T, compare, Hash>::emplace_hint(iterator hint, value_type&& x)
{
	return emplace(std::forward<value_type>(x)); 
}

template<typename Key, typename T, typename compare, typename Hash>
inline uint64_t HashMap<Key, T, compare, Hash>::erase(const key_type& x)
{
	uint64_t bucket;
	auto it = findElement(x, bucket);
	if (it != std::end(mBuckets[bucket]))
	{
		mBuckets[bucket].erase(it);
		mSize--;
		return 1;
	}
	else return 0; 
}
template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T,
compare, Hash>::iterator HashMap<Key, T, compare, Hash>::erase(iterator position)
{
	iterator next = position;
	++next;
	mBuckets[position.mBucketIndex].erase(position.mListIterator);
	mSize--;
	return next; 
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::iterator HashMap<Key, T, compare, Hash>::erase(iterator first, iterator last)
{
	for (iterator next = first; next != last; )
	{
		next = erase(next);  
	}
	return last; 
}

template<typename Key, typename T, typename compare, typename Hash>
inline typename
HashMap<Key, T, compare, Hash>::value_type* HashMap<Key, T, compare, Hash>::find(const key_type& k)
{
	uint64_t bucket;

	auto it = findElement(k, bucket);

	if (it == std::end(mBuckets[bucket]))
	{
		return end();
	}

	return hash_map_iterator<hash_map_type>(bucket, it, this); 
}

template<typename Key, typename T, typename compare, typename Hash>
inline const typename HashMap<Key, T, compare, Hash>::value_type*
HashMap<Key, T, compare, Hash>::find(const key_type& x) const
{
	uint64_t bucket;
	auto it = const_cast<hash_map_type*>(this)->findElement(x, bucket);

	if (it == std::end(mBuckets[bucket]))
	{
		return end(); 
	}

	return const_hash_map_iterator<hash_map_type>(bucket, it, this); 
}
template<typename Key, typename T, typename compare, typename Hash>
inline std::pair<typename HashMap<Key, T, compare, Hash>::iterator,
	typename HashMap<Key, T, compare, Hash>::iterator> HashMap<Key, T, compare, Hash>
	::equal_range(const key_type& x)
{
	auto it = find(x);

	return std::pair(it, it);
}
template<typename Key, typename T, typename compare, typename Hash>
inline const std::pair<
typename HashMap<Key,T,compare,Hash>::const_iterator, 
typename HashMap<Key, T, compare, Hash>::const_iterator> 
HashMap<Key, T, compare, Hash>::equal_range(const key_type& x) const
{
	auto it = find(x);

	return std::pair(it, it);
}
;
template<typename Key, typename T, typename compare, typename Hash>
inline uint64_t HashMap<Key, T, compare, Hash>::count(const key_type& x) const
{
	if (find(x) == end()) {
		return 0;
	}
	else {
		return 1;
	}
};

template<typename Key, typename T, typename compare, typename Hash>
inline T& HashMap<Key, T, compare, Hash>::operator[](const key_type& x)
{
	/*value_type* found = find(k);

	if (found == nullptr)
	{
		auto Inserter = std::pair(k, std::forward<T>(T()));

		auto& [x, Second] = Inserter;

		insert(std::move_if_noexcept(Inserter));
		return Second;;
	};*/
	return ((insert(std::make_pair(x, T()))).first)->second;
}
template<typename Key, typename T, typename compare, typename Hash>
inline bool HashMap<Key, T, compare, Hash>::empty() const
{
	return mSize == 0;
}
template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::size_type HashMap<Key, T, compare, Hash>::size() const
{
	return this->mSize;
}
template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::size_type HashMap<Key, T, compare, Hash>::max_size() const
{
	return mBuckets[0].max_size();
}
template<typename Key, typename T, typename compare, typename Hash>
inline void HashMap<Key, T, compare, Hash>::swap(hash_map_type& hashIn)
{
	std::swap(*this, hashIn);
}
template<typename Key, typename T, typename compare, typename Hash>
inline void HashMap<Key, T, compare, Hash>::clear() noexcept
{
	for (auto& bucket : mBuckets)
	{
		bucket.clear(); 
	}
	mSize = 0;  
}
template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap
<Key, T, compare, Hash>::key_compare HashMap<Key, T, compare, Hash>::
key_comp() const
{
	return mComp;
};
template<typename Key, typename T, typename compare, typename Hash>
inline typename HashMap<Key, T, compare, Hash>::value_compare 
HashMap<Key, T, compare, Hash>::value_comp() const
{
	return value_compare(mComp); 
};

template<typename Key, typename T, typename compare, typename Hash>
template<typename InputIterator>
inline HashMap<Key, T, compare, Hash>::HashMap
(InputIterator first, InputIterator last, const compare& comp, 
uint64_t numBuckets, const Hash& hash)
	:
	mSize(0),mComp(comp),mHash(hash)

{
	if (numBuckets == 0)
	{
		throw std::invalid_argument("Number of buckets must be positive!");
	}
	mBuckets.resize(numBuckets);
	insert(first,last);
}

template<typename Key, typename T, typename compare, typename Hash>
template<typename InputIterator>
inline void HashMap<Key, T, compare, Hash>::insert(InputIterator first, InputIterator last)
{
    auto Istr = std::inserter(*this,this->begin());

	std::copy(first, last, Istr); 
}
