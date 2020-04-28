
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
// ����� ���ӽ����̽� using Ű����� �ſ� ������ ������� ����ڿ���
// ���ӽ����̽��� �����ο� ����� ���Ѵ¼�
// ...������ ���� ���Ǹ� ����
using namespace std; 
class num_iterator
{
public:
	using value_type = int32_t;
	// datatype-> iterator ������ �Ͻ����� ��ȯ�� ���ƹ�����.
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
// �̷��Ը��ص� ranged for ������ �������� ������ ������ 
// iterator_traits ���� ���������
// iterator �� ��� �޴� ����� ������ C++17 ���� ����� ������ �Ǿ���ȴ�.
namespace std {
	template<>
	struct iterator_traits<num_iterator> {
		using iterator_category = std::forward_iterator_tag;  
		using value_type = typename num_iterator::value_type;
		// �ݺ��ڰ��� �Ÿ��� ��Ÿ���� Ÿ�� distance(lhs - rhs);
		using difference_type = void; 
		// ��Ҹ� �����ϱ����� �����Ͱ� �ʿ��ϴٸ� �������ش�
		using pointer = value_type*;
		// �����Ϳ� �Ȱ���
		using reference = value_type&;
		// STL �˰����� iterator_traits<my_iterator> �� ����
		// Ÿ�������� ������.
	};
};

