#include <iostream>
#include <vector> 
#include <algorithm>
#include <thread>
using namespace std; 

bool isDigit(char symbol) {
	return (symbol >= 48 && symbol <= 57);
}
int main() {
	for (int i = 100; true; --i) {
		std::this_thread::sleep_for(10ms);
		std::cout << std::clamp(i, 0, 100);
	}
}
