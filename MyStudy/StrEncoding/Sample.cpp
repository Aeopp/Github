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

	//���ڹ߰�
	//���� ���� ù��° ���ε� ������ ���ε� ������
	// �ε��� ���̰� ������ �׳� �ױ��� Ǫ�ù� �ϰ�Ѿ
	// �ε��� ���̰� ������ �ε��� ���� ��������� �˾Ƴ���
	//���� Ǫ�ù� ���� Ǫ�ù�
	// 2ĭ��ŭ �ǳʶپ �Ѿ

int main()
{
	std::string Str = "ccccccccccccccc";
	std::cout << lineEncoding(Str);
};
