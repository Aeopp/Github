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
	cout << Start << " ���� " << End << " ������ ���� " << Sum << " �Դϴ�.\n";
	Sum = 0;
	while (i--)
	{
		Sum += i;
	};
	cout << Start << " ���� " << End << " ������ ���� " << Sum << " �Դϴ�.\n";
	Sum = 1;
	do
	{
		Sum += i;
	} while (++i<=End);
	cout << Start << " ���� " << End << " ������ ���� " << Sum << " �Դϴ�.\n";
	return 0;
};