// ������ �Է¹޴´�.
// 1. if - else �б�� ������ ����
// �����ϰ� ����Ѵ�.
// 2. switch-case ������ �����۾�

#include <iostream>
#include <string>activecf.h
using namespace std;

int main(void)
{
	int TotalScore;
	char GPA;
	cin >> TotalScore;

	if (0 <= TotalScore <= 100)
	{
		cout << TotalScore << " ������ ��ȿ�մϴ�." << endl;
	}
	else {
		cout << TotalScore << " ������\
		��ȿ���� �ʽ��ϴ�.";
		return 0;
	};

	if (60 <= TotalScore)
	{
		cout << TotalScore << " ���� �̻��� �հ� �����Դϴ�.";
	}
	else 
		cout << TotalScore << " ���� �̻��� ���հ� �����Դϴ�.";
	if (TotalScore >= 90)
		GPA = 'A';
	else if (TotalScore >= 80)
		GPA = 'B';
	else if (TotalScore >= 70)
		GPA = 'C';
	else if (TotalScore >= 60)
		GPA = 'D';
	else
		GPA = 'F';

	cout << "�л��� ������ " << GPA << " �Դϴ�.";


	switch (TotalScore / 10)
	{
	case 9:
		GPA = 'A';
		break;
	case 8:
		GPA = 'B';
		break;
	case 7:
		GPA = 'C';
		break;
	case 6:
		GPA = 'D';
		break;
	default:
		GPA = 'F';
		break;
	};
	cout << "�л��� ������ " << GPA << " �Դϴ�.";
};