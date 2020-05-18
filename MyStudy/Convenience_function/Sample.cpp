#include <conio.h>
#include <iostream>
#include <type_traits>
#include <memory>
#include <string>
#include <valarray>
#include <type_traits>
#include <math.h>
#include <Windows.h>
#include <thread>
#include <complex>
#include <utility>
#include <numbers>
using  namespace  std;

using vector=std::valarray<int32_t> ;
void gotoxy(int x, int y)
{
    COORD Pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void main()
{
   /* constexpr std::complex<double_t> PI = std::numbers::pi;
    constexpr std::complex<double_t> DefaultAngle = 1.i;
    constexpr auto Radius = 30.i;
    const std::complex<double_t> Radian = PI / 180.0  ;
    constexpr std::pair Center{ 30.i,30.i };
    std::pair Pos{ Center};
    std::complex<double_t> Angle = DefaultAngle;
    
    while (true)    {
        Angle += 1.i;
        if (real(Angle)>= 360.)
        {
            Angle = DefaultAngle;
    	}
        auto& [x, y] = Pos;
    	
        x = std::sin(Angle*Radian)  *20.i + Center.first;
        y= std::cos(Angle * Radian) *10.i + Center.second;
        gotoxy(real(x),real(y));
        std::cout << "S";
        std::this_thread::sleep_for(5ms);
    }*/
    double_t pi = 3.141592;
    double_t radian = 180. / pi;
    double_t angle = 1.;
    double_t radius = 25.;
	while(true)
	{
        if (angle >= 360) {
            system("cls");
            angle = 1;
        }
        int x= sin(angle / radian) * radius + 50;
        int y = cos(angle / radian) * radius + 50;
        gotoxy(x, y);
        cout << 'S';
        angle += 0.1;
        this_thread::sleep_for(1ms);
	}



}