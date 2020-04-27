#include <iostream>
#include <unordered_map>
#include <utility>
struct coord {
	int x;  int y;
	bool operator==(const coord& rhs)const {
		return x == rhs.x && y == rhs.y; 
	};
};
// ���̺귯�̿� �̹� �����Ǿ��ִ� hash<type> �� 
// ���� ���� ���� ����ü�� ���ø� Ư��ȭ ������ ���ӽ����̽��� ���
// �߰������ش�. 
namespace std {
	template<>
	struct hash<coord>
	{
		using argument_type = coord;
		using result_type = size_t;
		result_type operator()(const argument_type& rhs)const
		{
			return static_cast<result_type>(rhs.x)
				+ static_cast<result_type>(rhs.y);
		};
		
	};
	template<>
	struct equal_to<coord>
	{
		using second_argument_type = coord;
		using first_argument_type = coord; 
		using result_type = size_t;
		constexpr bool operator()(const first_argument_type& lhs,const second_argument_type& rhs)const
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		};
	};
};

int main() {
	std::unordered_map<coord, int> hash_map{ 
		{ {1,2} , 1}, { {2,3},2 }, { {4,5} ,3 }
	}; 
	for (const auto& [key, value] : hash_map) {
		std::cout << key.x << " " << key.y << " " << value; 
	};

	std::equal_to<coord> abc;
	
};
