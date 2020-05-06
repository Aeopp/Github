#pragma once
#include <windows.h>
#include <string>
#include <type_traits>
#include "Util.h"

class Bitmap
{
private:
	HBITMAP_ptr _HBitmap;
	HDC_ptr _HScreenDC;
public:
	HDC_ptr _HMemDc;
	BITMAP _BmpInfo;
	//template<typename _HDCptr/*,
	///*typename =std::enable_if_t<std::is_same_v<HDC_ptr, _HDCptr>,int>*/>*/
	bool Load(HDC_ptr  ScreenHandle,std::wstring Name)noexcept;
	inline bool Clear()noexcept;
	
	Bitmap() = default;
	~Bitmap() noexcept = default;
	Bitmap(Bitmap&&) noexcept = default;
	Bitmap(const Bitmap&) = default;
	Bitmap& operator=(Bitmap&&) noexcept = default;
	Bitmap& operator=(const Bitmap&) = default;
};

inline bool Bitmap::Clear() noexcept
{
	DeleteObject(_HBitmap.get());
	ReleaseDC(world::HWnd.get(), _HMemDc.get());
	return true;
};

//template <typename _HDCptr/*, typename*/>
bool Bitmap::Load(HDC_ptr ScreenHandle, std::wstring Name) noexcept
{
	//_HScreenDC = std::forward<HDC_ptr>(ScreenHandle);
	////_HScreenDC = ScreenHandle;

	//_HBitmap =
	//	std::move(HBITMAP_ptr(util::LoadImage_To_BitMap(Name)(), util::Bitmap_Deleter()));

	//GetObject(_HBitmap.get(), sizeof(HBITMAP__), &_BmpInfo);
	//
	//_HMemDc =std::move(HDC_ptr
	//(CreateCompatibleDC(_HScreenDC.get()),
	//	util::ScreenDC_Deleter(world::HWnd)));
	
	/*SelectObject(_HMemDc.get(), _HBitmap.get());*/
	
	return true; 
}
