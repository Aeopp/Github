#pragma once
#include "Utility.h"
#include "Object.h"

class Bitmap : public Object
{
public:
	tstring		Filename;
	BITMAP		BmpInfomation;
	std::weak_ptr<HDC__> ScreenHDC;
	std::unique_ptr<HDC__, decltype(HDCDeleteDC)> MemoryHDC;
	std::unique_ptr<HBITMAP__,decltype(ObjectDeleter)>	BitmapHandle;
public:
	bool	Frame();
	bool	Render();
public:
	Bitmap(std::shared_ptr<HDC__> SharedScreenDC, tstring szLoadFileName);
	~Bitmap();
	Bitmap(Bitmap&&)noexcept = default;
	Bitmap& operator=(Bitmap&&)noexcept = default;
	Bitmap(const Bitmap& Rhs) = delete;
	Bitmap& operator=(const Bitmap&Rhs) = delete;
};
