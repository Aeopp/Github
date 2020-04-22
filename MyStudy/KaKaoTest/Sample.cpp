
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
string foo(int32_t number, int32_t n)
{
    const std::string table = "0123456789ABCDEF";
    std::string str;
    const int32_t q = n;
    int32_t m = 1;
    while (number)
    {
        int32_t temp = number % n;
        int32_t temp2 = temp / m;
        m = m * q;
        str.push_back(table[temp2]);
        number -= temp;
        n *= q;
    }
    std::reverse(std::begin(str), std::end(str));

    return str;
}

string solution(int n, int t, int m, int p) {
    // 진법 n , t 구할 개수 , m 인원  p순서
    int32_t number = -1;
    std::string buffer = "0";

    for (int32_t i = 0; i < (m * t); ++i)
    {
        buffer += foo(++number, n);
    }
    std::string answer;
    int32_t jump = (m - p) + (p);
    for (int32_t i = p - 1; i < t * m; i += jump)
    {
        answer.push_back(buffer[i]);
    }
    return answer;
}