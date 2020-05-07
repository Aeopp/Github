#pragma once
#include <windows.h>
#include <string>
#include <type_traits>
#include "Util.h"
#include "ObjectSuper.h"
class Bitmap : public ObjectSuper
{
private:
	HBITMAP_ptr _HBitmap;
	HDC_ptr _HScreenDC;
public:
	HDC_ptr _HMemDc;
	BITMAP _BmpInfo;
	std::wstring _Name;

	virtual bool  Init()noexcept{return true;}
	virtual bool Frame()noexcept { return true; }
	virtual bool Render()noexcept{	return true;}
	
	bool Load(HDC_ptr ScreenHandle, const std::wstring& Fullpath,
		const std::wstring& filename)noexcept;
	inline bool Clear()noexcept;
	
	Bitmap();
	~Bitmap() noexcept = default;
	Bitmap(Bitmap&&) noexcept = default;
	Bitmap(const Bitmap&) = default;
	Bitmap& operator=(Bitmap&&) noexcept = default;
	Bitmap& operator=(const Bitmap&) = default;
};
Bitmap::Bitmap()
{
	Init();
};

inline bool Bitmap::Clear() noexcept
{
	DeleteObject(_HBitmap.get());
	ReleaseDC(world::HWnd.get(), _HMemDc.get());
	return true;
};
// TODO :: DDB Device Dependency Bitmap 디바이스 종속적 비트맵
// TODO :: DIB Device InDependency Bitmap 디바이스 독립적 비트맵
bool Bitmap::Load(HDC_ptr ScreenHandle,const std::wstring& Fullpath,
	const std::wstring& filename) noexcept
{
	_HScreenDC = std::move(ScreenHandle);
	
	if (_HBitmap =
		HBITMAP_ptr(util::LoadImage_To_BitMap(Fullpath)(), util::Bitmap_Deleter()))
	{
		_Name = filename;
	}
	else
	{
		return false; 
	}
	
	GetObject(_HBitmap.get(), sizeof(HBITMAP__), &_BmpInfo);
	
	_HMemDc =HDC_ptr
	(CreateCompatibleDC(_HScreenDC.get()),
		util::ScreenDC_Deleter(world::HWnd));
	
	SelectObject(_HMemDc.get(), _HBitmap.get());
	
	return true; 
}
