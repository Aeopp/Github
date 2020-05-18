#pragma once

struct Resolution {
	unsigned int iW;
	unsigned int iH;
};

struct POSITION {
	float x;
	float y;
	POSITION() :
		x(0.f),
		y(0.f) {};
	POSITION(float _x, float _y) :
		x{ _x },
		y(_y){};
	POSITION(const POSITION& Pos) {
		x = Pos.x;
		y = Pos.y;
	}; 
	POSITION(const POINT& pt) {
		x = pt.x;
		y = pt.y;
	}; 
	POSITION& operator=(const POSITION& pos) {
		if (this == &pos) return *this; 
		x = pos.x;
		y = pos.y;
		return *this; 
	};
	POSITION& operator=(const POINT& pt) {
		x = pt.x;
		y = pt.y;
		return *this;
	};
	POSITION operator+ (const POSITION& pos) {
		POSITION tPos;
		tPos.x = x + pos.x;
		tPos.y = y + pos.y;
		return tPos;
	};
	POSITION operator+ (const POINT& pt) {
		POSITION tPos;
		tPos.x = x + pt.x;
		tPos.y = y + pt.y;
		return tPos;
	};
	POSITION operator+(float f)
	{
		POSITION tPos;
		tPos.x = x + f;
		tPos.y = y  + f;
		return tPos; 
	}



	POSITION operator- (const POSITION& pos) {
		POSITION tPos;
		tPos.x = x - pos.x;
		tPos.y = y - pos.y;
		return tPos;
	};
	POSITION operator- (const POINT& pt) {
		POSITION tPos;
		tPos.x = x - pt.x;
		tPos.y = y - pt.y;
		return tPos;
	};
	POSITION operator-(float f)
	{
		POSITION tPos;
		tPos.x = x - f;
		tPos.y = y - f;
		return tPos;
	}


	POSITION operator/ (const POSITION& pos) {
		POSITION tPos;
		tPos.x = x / pos.x;
		tPos.y = y / pos.y;
		return tPos;
	};
	POSITION operator/ (const POINT& pt) {
		POSITION tPos;
		tPos.x = x / pt.x;
		tPos.y = y / pt.y;
		return tPos;
	};
	POSITION operator/(float f)
	{
		POSITION tPos;
		tPos.x = x / f;
		tPos.y = y / f;
		return tPos;
	}
};

using _SIZE = POSITION;

