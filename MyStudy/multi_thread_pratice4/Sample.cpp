#include <iostream>
#include <thread> 
#include <mutex> 
#include <algorithm>
#include <numeric>
#include <vector> 
using namespace std;

std::mutex  MUTEX; 
std::vector<int32_t> Vector;

void foo(int left,int right) {
	// auto q = { 1,2,3,4,5 };
	// auto b = { 1,2,3,4,5 }; 

	auto sum = std::accumulate(begin(Vector)+ left,begin(Vector)
		+right,0);

	MUTEX.lock();
	std::cout << sum << endl;
	MUTEX.unlock();
}

int main() {
	for (int i = 0; i < 10000000; ++i)
	{
		Vector.push_back(i); 
	}
	
	auto NOW = chrono::system_clock::now(); 
	auto a5 = thread{ foo, 0,10000000 };
	a5.join();
	chrono::duration<double> time = (chrono::system_clock::now() - NOW); 
	std::cout << time.count() << endl << endl << endl << endl;




	NOW = chrono::system_clock::now();
	auto a1 = thread{ foo, 0,10000000 / 4 };
	auto a2 = thread{ foo, 10000000 / 4,10000000 / 2 };
	auto a3 = thread{ foo, 10000000 / 2,(10000000 * 0.75) };
	auto a4 = thread{ foo, (10000000 * 0.75) ,10000000 };
	a1.join();
	a2.join();
	a3.join();
	a4.join();
	time = (chrono::system_clock::now() - NOW);
	std::cout << time.count() << endl << endl << endl;
}