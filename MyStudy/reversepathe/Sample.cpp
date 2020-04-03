#include <vector>
#include <iostream>
#include <numeric>
#include <algorithm>
using namespace std;

int avoidObstacles(std::vector<int> inputArray) 
{
	auto& ar = inputArray; 
	std::sort(inputArray.begin(), inputArray.end());
	int maxele = ar.back(); 
	int res= std::numeric_limits<int>::max();

	int pos = 0;
	int jump = 1;
	int count = 0;

	while (jump < maxele)
	{
		if (ar.end() == std::find(ar.begin(), ar.end(), pos))
		{
			pos += jump;
			count++;
			if (pos > maxele)
			{
				res = std::min(res, count);
				count = 0; 
				pos = 0; 
				jump++;
			};
		}
		else
		{
			pos = 0;
			jump++;
			count = 0;
		}
	};
	
		
	return res; 
}
int main()
{
	cout << avoidObstacles({5,3,6,7,9});
};
