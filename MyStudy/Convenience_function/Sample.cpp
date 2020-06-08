#include <iostream>
#include <numeric>
#include <Windows.h>

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
};

int main() {
	int32_t x = 0;
	int32_t  b = 3;
	int32_t   y = 0;

	for (uint32_t i = 0; i < INT_MAX; ++i) {
		y = 1 *i + b;
		gotoxy(x, y);
		std::cout << '*';
	}
}