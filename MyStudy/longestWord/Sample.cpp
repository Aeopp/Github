#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <array>
#include <utility>
#include <cmath>


int sumUpNumbers(std::string inputString
= "there are some (12) digits 5566 in this 770 string 239") {
	std::stringstream ss (inputString);
	int32_t sum = 0;
	int32_t temp;
	std::string buf;
	while (1)
	{
		ss >> temp;
		ss >> buf;
		sum += temp;

	}
	return sum;
}

int main()
{
	std::cout << sumUpNumbers();
};
