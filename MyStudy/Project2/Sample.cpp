// 점수를 입력받는다.
// 1. if - else 분기로 점수에 따라
// 검증하고 출력한다.
// 2. switch-case 문으로 동일작업

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
		cout << TotalScore << " 점수는 유효합니다." << endl;
	}
	else {
		cout << TotalScore << " 점수는\
		유효하지 않습니다.";
		return 0;
	};

	if (60 <= TotalScore)
	{
		cout << TotalScore << " 점수 이상은 합격 점수입니다.";
	}
	else 
		cout << TotalScore << " 점수 이상은 불합격 점수입니다.";
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

	cout << "학생의 학점은 " << GPA << " 입니다.";


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
	cout << "학생의 학점은 " << GPA << " 입니다.";
};