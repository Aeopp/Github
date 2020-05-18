#include "game.h"
#include <algorithm>
#include "Time.h"
#include <numbers>
void game::Run()
{
	auto hdc = window::get_hdc().lock();
	Input_check();
	helper::clamp_pos(window::hWnd, player_Rect, { Width,Height },Center);
	auto& [left, top, right, bottom] = player_Rect;
	Rectangle(hdc.get(), left, top, right, bottom);
	Ellipse(hdc.get(), Center.first-5, Center.second-5, Center.first, Center.second);
	for (auto& Bullet : Temp::Bullets) {
		Bullet.Frame(); 
	}
};

void game::Input_check() noexcept
{
	auto DeltaTime = Time::Instance().DeltaTime();

	auto& [left, top, right, bottom] = player_Rect;
	auto Vec = player_speed* DeltaTime; 

	if (GetAsyncKeyState('A') & 0x8000) {
		right -= (Vec);
		left -= (Vec);
	}
	if (GetAsyncKeyState('D') & 0x8000) {
			right += (Vec);
		left += (Vec);
	}
	if (GetAsyncKeyState('W') & 0x8000) {
		top -= (Vec);
		bottom -= (Vec);
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		top += (Vec);
		bottom += (Vec);
	};

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		POINT mousepos;
		window::GetMousePos(mousepos);
		Ellipse(window::get_hdc().lock().get(), mousepos.x - 5, mousepos.y - 5, mousepos.x, mousepos.y);
		MoveToEx(window::get_hdc().lock().get(),Center.first,Center.second,NULL);
		LineTo(window::get_hdc().lock().get(), mousepos.x, mousepos.y);

		float dis_x = std::abs(Center.first- mousepos.x);
		float dis_y = std::abs(Center.second- mousepos.y);
		float dinstance = std::sqrt(dis_x* dis_x+ dis_y* dis_y);

		float angle = std::atanf((   static_cast<double>(Center.second  - mousepos.y) / static_cast<double>(  Center.first- mousepos.x)));
		float cos_x = std::cosf((angle));
		float sin_y = std::sinf((angle));

		auto print = window::format_text("Distance :  ",dinstance,"   Angle : ",angle,"   Cos :",cos_x,"   Sin :",sin_y);

		TextOut(window::get_hdc().lock().get(),setup::ResoluctionWidth/3,setup::ResoluctionHeight/5, print.c_str(), print.size());
		Temp::Bullet Bullet;

		Bullet.Sphere.left = Center.first + cos_x * Bullet.radius ; 
		Bullet.Sphere.top = Center.second  + sin_y* Bullet.radius;
		Bullet.Sphere.right = Bullet.Sphere.left + Bullet.radius; 
		Bullet.Sphere.bottom = Bullet.Sphere.top + Bullet.radius;
		Bullet.angle = angle; 

		Temp::Bullets.push_back(Bullet);
		//POINT mousepos;
		//window::GetMousePos(mousepos);
		//float Center_X = right + left / 2; 
		//float Center_Y = bottom + top / 2;
		//float x = (mousepos.x - Center_X);
		//float y = (mousepos.y - Center_Y); 
		//float theta = std::atan(y/x); 
		//float cos_theta = std::cos(math::DegreeToRadian(theta));
		//float sin_theta = std::sin(math::DegreeToRadian(theta));
		//// �÷��̾��� ���͸� ���Ѵ�.
		//// �÷��̾��� ���Ϳ��� ���콺 ������ �� x y ������ ���밪�� ���Ѵ�.
		//// ���� ���밪���� ��ũź��Ʈ�� ������ ������ �˾Ƴ���.
		//// ���� ������ ���� �ڻ����� ������ x ,y ������ ���Ѵ�.
		//// ������ �ޱ۰��� �־��ش�. 
		//// ������ �������� ���� ��ġ�� �Ѿ��� ������Ų��.
		
	}
}




