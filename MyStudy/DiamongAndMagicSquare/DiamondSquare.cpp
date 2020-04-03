#include <iostream> 
#include <vector>
using namespace std;

void DiamondPrint(const int n)
{	
	for (int loop = 0; loop < 3; ++loop)
	{
		int dia = 1;
		int bac = n - 1;

		for (int i = 0; i < n * 2 - 1; ++i)
		{
			for (int j = 0; j < bac; ++j)
			{
				cout << ' ';
			}
			for (int k = 0; k < dia; ++k)
			{
				cout << '*';
			};

			if (i >= n - 1)
			{
				dia -= 2;
				bac++;
			}
			else if (i < n)
			{
				dia += 2;
				bac--;
			}
			cout << endl;
		};
	};
};

 // 행은 감소하고 열은 증가합니다.
// 행이 0 보다 작아지면 최대행으로 이동합니다.
// 열이 최대열보다 커지면 0으로 이동합니다.
 // 만약 이동한 곳이 이미 마킹되어있다면 
 // 이동하기전 아래 행으로 이동합니다.
void MagicSquarePrint(const int n)
{
	int squ[100][100] = { 0, };

	int row = 0;
	int col = n / 2;
	int num = 1;
	squ[row][col] = num++;
	for (int i = 0; i < n*n - 1; ++i)
	{
		int brow = row;
		int bcol = col;
		row--;
		col++;
		if (row < 0) row = n - 1;
		if (col > (n - 1)) col = 0;
		if (squ[row][col] != 0)
		{
			row = brow + 1;
			col = bcol;
		};
		squ[row][col] = num++;
	};
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << squ[i][j] << ' '; 

		}cout << endl;
	};
};
 int main()
{
	//int n;
	//cin >> n;
	//DiamondPrint(n);

	int n;
	cin >> n;
	MagicSquarePrint(n); 
};

