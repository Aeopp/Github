#include <iostream>

int main(void)
{
	using std::cout;
	using std::endl;
	using std::cin;

	int Start, End, Sum = 0;
	cin >> Start >> End;
	int i = Start;
	for (; i <= End; ++i)
	{
		Sum += i;
	};
	cout << Start << " 부터 " << End << " 까지의 합은 " << Sum << " 입니다.\n";
	Sum = 0;
	while (i--)
	{
		Sum += i;
	};
	cout << Start << " 부터 " << End << " 까지의 합은 " << Sum << " 입니다.\n";
	Sum = 1;
	do
	{
		Sum += i;
	} while (++i<=End);
	cout << Start << " 부터 " << End << " 까지의 합은 " << Sum << " 입니다.\n";
	return 0;
};