#include <vector>
#include <algorithm>

bool isseq(const std::vector<int>& vec)
{
	int be = vec[0];
	for (int i = 1; i < vec.size(); ++i)
	{
		if (be < vec[i])
			be = vec[i];
		else
			return false;
	};
	return true;
};
bool almostIncreasingSequence(const std::vector<int>& copy)
{
	if (copy.size() == 2)
		return true;

	for (int i = 0; i < copy.size(); ++i)
	{
		auto temp = copy;
		temp.erase(temp.begin() + i);
		if (isseq(temp))
			return true;
	};
	return false;
	
};
class se
{
protected: 
	virtual void aa() {};
};
class s : public se
{
	virtual void aa() override
	{
		__super::aa();
		aa();
		return; 
	};
};

#include <iostream>
int main()
{
 std::	 cout << almostIncreasingSequence({30,60,50,80,100,200,150} );
};