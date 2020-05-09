#pragma once
#include "Utility.h"
#include "Object.h"


class Bitmap : public Object
{
private:
	// Release Device Context
	static inline auto HDCDeleter = [](HDC DisplayHandle) {
		ReleaseDC(World::WindowHandle, DisplayHandle);
	};
	static inline auto BitmapHandleDeleter = [](HBITMAP BitmapHandle) {
		DeleteObject(BitmapHandle);
	};
public:
	std::unique_ptr<HBITMAP__,decltype(BitmapHandleDeleter)>		BitmapHandle;
	std::unique_ptr<HDC__, decltype(HDCDeleter)>	MemoryHDC;
	std::unique_ptr<HDC__,decltype(HDCDeleter)>	ScreenHDC;
	BITMAP		BmpInfomation;
	tstring		Filename;
public:
	bool	Frame();
	bool	Render();
public:
	Bitmap(HDC hScreenDC, tstring szLoadFileName);
	~Bitmap();
	Bitmap(Bitmap&&)noexcept = default;
	Bitmap& operator=(Bitmap&&)noexcept = default;
	Bitmap(const Bitmap& Rhs) = delete;
	Bitmap& operator=(const Bitmap&Rhs) = delete;
};

