
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
// 헤더에 네임스페이스 using 키워드는 매우 안좋다 헤더파일 사용자에게
// 네임스페이스의 자유로운 사용을 빼앗는셈
// ...이지만 구현 편의를 위해
using namespace std; 
class num_iterator
{
public:
	using value_type = int32_t;
	// datatype-> iterator 으로의 암시적인 변환을 막아버린다.
	explicit num_iterator(int32_t position = 0) : value{ position } {};
	int32_t operator*()const { return value; }; 
	num_iterator& operator++() {
		++value;
		return *this;
	}; 
	bool operator!=(const num_iterator& rhs) const {
		return value != rhs.value;
	};
	class num_range {
		int32_t left; int32_t right;
	public:
		num_range(int32_t p_left, int32_t p_right) :
			left{p_left},
			right{ p_right }
		{};
		num_iterator begin() const { return num_iterator{ left}; };
		num_iterator end() const { return num_iterator{ right }; };
	};
private: 
	value_type  value;
};
// 이렇게만해도 ranged for 까지는 문제없이 돌릴수 있지만 
// iterator_traits 까지 만들어주자
// iterator 를 상속 받는 방법도 있지만 C++17 부터 비권장 문법이 되어버렸다.
namespace std {
	template<>
	struct iterator_traits<num_iterator> {
		using iterator_category = std::forward_iterator_tag;  
		using value_type = typename num_iterator::value_type;
		// 반복자간의 거리를 나타내는 타입 distance(lhs - rhs);
		using difference_type = void; 
		// 요소를 참조하기위해 포인터가 필요하다면 정의해준다
		using pointer = value_type*;
		// 포인터와 똑같다
		using reference = value_type&;
		// STL 알고리즘은 iterator_traits<my_iterator> 를 통해
		// 타입정보에 접근함.
	};
};

