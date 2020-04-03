#include <iostream>
#include <random>
using namespace std;



int main(void)
{
    std::random_device RandomDevice; 
    std::mt19937 Gen(RandomDevice()); // 랜덤디바이스로 엔진 초기화
    std::uniform_int_distribution<int> Distribution(0, 100); // 0~100; 분포
    size_t LCount = 0;
    for (;;)
    {
        LCount++;
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " 번 반복되었다.\n";            break;

        };
    };
    LCount = 1;
    while (true)
    {
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " 번 반복되었다." << endl;            break;

        };
        LCount++;
    }; LCount = 1;
    do
    {
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " 번 반복되었다." << endl;
            break;
        };
        LCount++;
    } while (true);
};