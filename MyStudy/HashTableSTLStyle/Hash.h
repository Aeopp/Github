#pragma once
#include <iostream>
#include <string>
template<typename T>
class Hash
{
public:
	uint64_t inline operator()(const T& key)const noexcept;
};
template<typename T>
uint64_t inline Hash<T>::operator()(const T& key) const noexcept
{
	uint64_t bytes = sizeof(key);
	uint64_t res = 0;
	for (uint64_t i = 0; i < bytes; ++i)
	{
		uint8_t b = *((unsigned char*)(&key) + i);
		res += b;
	};
	return res;
};
inline uint64_t Hash<std::string>::operator()
(const std::string& key) const noexcept
{
	uint64_t sum = 0;
	for (uint64_t i = 0; i < key.size(); ++i)
		sum += static_cast<uint8_t>(key[i]);
	return sum;
}
