#pragma once
#include "Bitmap.h"
#include <valarray>

struct Sphere {
	POINT Center;
	float_t Radius; 
};
class Collision
{
public:
	static inline bool RectInPoint(const RECT Lhs, const POINT Rhs);
	static inline bool RectInRect(const RECT Lhs, const  RECT Rhs);
	static inline bool SphereInPoint(const  Sphere Lhs, const  POINT Rhs);
	static inline bool SphereInSphere(const Sphere Lhs , const Sphere Rhs);
};
inline bool Collision::RectInPoint(const RECT Lhs, const POINT Rhs)
{
	if (Lhs.left <= Rhs.x && Lhs.right >= Rhs.x) {
		if (Lhs.top <= Rhs.y && Lhs.bottom >= Rhs.y) {
			return true;
		}
	}
	return false;
};

inline bool Collision::RectInRect(const RECT Lhs, const RECT Rhs)
{
	POINT LhsCenter, RhsCenter;
	LhsCenter.x = (Lhs.left + Lhs.right) / 2;
	LhsCenter.y = (Lhs.top + Lhs.bottom) / 2;
	RhsCenter.x = (Rhs.left + Rhs.right) / 2;
	RhsCenter.y = (Rhs.top + Rhs.bottom) / 2;

	if (std::abs(LhsCenter.x - RhsCenter.x) > (Lhs.right - Lhs.left) / 2 + (Rhs.right - Rhs.left) / 2
		|| (std::abs(LhsCenter.y - RhsCenter.y) > (Lhs.bottom - Lhs.top) / 2 + (Rhs.bottom - Rhs.top) / 2)) {
		return false;
	}
	else return true;
};

inline bool Collision::SphereInPoint(const Sphere Lhs, const POINT Rhs)
{

	if (std::sqrt((Lhs.Center.x - Rhs.x)* (Lhs.Center.x - Rhs.x) + (Lhs.Center.y - Rhs.y)* (Lhs.Center.y - Rhs.y)) < Lhs.Radius) {
		return true;
	}
	else return false;
}

inline bool Collision::SphereInSphere(const Sphere Lhs, const Sphere Rhs)
{
	return SphereInPoint(Lhs, Rhs.Center);
}

