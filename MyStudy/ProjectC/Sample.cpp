#include <iostream>
#include <random>
using namespace std;



int main(void)
{
    std::random_device RandomDevice; 
    std::mt19937 Gen(RandomDevice()); // ��������̽��� ���� �ʱ�ȭ
    std::uniform_int_distribution<int> Distribution(0, 100); // 0~100; ����
    size_t LCount = 0;
    for (;;)
    {
        LCount++;
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " �� �ݺ��Ǿ���.\n";            break;

        };
    };
    LCount = 1;
    while (true)
    {
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " �� �ݺ��Ǿ���." << endl;            break;

        };
        LCount++;
    }; LCount = 1;
    do
    {
        if (Distribution(Gen) == 77)
        {
            cout << LCount << " �� �ݺ��Ǿ���." << endl;
            break;
        };
        LCount++;
    } while (true);
};