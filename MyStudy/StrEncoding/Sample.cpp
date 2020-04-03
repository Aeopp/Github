#include <iostream>
#include <string>
std::string r, lineEncoding(std::string s) {
	for (auto i = begin(s), j = i; i != end(s); i = j) {
		while (*j == *i) ++j;
		r.append(j - i > 1 ? std::to_string(j - i) : ""s).push_back(*i);
	}
	return r;
}
std::string lineEncoding(std::string s) {
	if (s.size() == 1)
		return s;

	std::string ret;

	//int32_t Q = s.find_first_not_of(s[0],0);

	//if (Q==-1)
	//{
	//	int32_t Interger = s .size() ;
	//	
	//	ret.push_back(static_cast<char>(Interger + 48));

	//	ret.push_back(s[0]);
	//	return ret;
	//};

	
	for (int32_t i = 0; i < s.size();)
	{
		char ch = s[i];
		int32_t right = s.find_first_not_of(ch, i);

		if (i == (right - 1))
		{
			ret.push_back(ch);
			++i;
		}
		else 
		{
			if (right == -1)
			{
				right = s.size();
			};
			int32_t Interger = right - i;
			if (Interger != 1)
				ret += std::to_string(Interger);

			ret.push_back(ch);
			i = right;
		}
	}
	return ret;
};

	//글자발견
	//글자 저장 첫번째 파인드 마지막 파인드 돌려봄
	// 인덱스 차이가 없으면 그냥 그글자 푸시백 하고넘어감
	// 인덱스 차이가 있음면 인덱스 빼서 몇글자인지 알아내고
	//숫자 푸시백 글자 푸시백
	// 2칸만큼 건너뛰어서 넘어감

int main()
{
	std::string Str = "ccccccccccccccc";
	std::cout << lineEncoding(Str);
};
