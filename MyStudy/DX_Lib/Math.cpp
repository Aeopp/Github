#include "Math.h"
#include "Window.h"

FVector3 Math::ScreenToNDC(FVector2 Coordinate)
{
	auto& [x, y] = Coordinate;
	const auto[left,top,right,bottom] = Window::Instance().GetClientRT();

	FVector3 v;
	v.x = ((float)x / (float)right) * 2.0f - 1.0f; //-1.0f;
	v.y = -(((float)x  / (float)bottom) * 2.0f - 1.0f);// 1.0f;

	return v;
}
