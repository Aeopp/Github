#pragma once

#include <windows.h>
#include <string>
#include <type_traits>
#include "Util.h"
#include "ObjectSuper.h"

class Bitmap : public Object
{
private:
	HBITMAP _HBitmap;
	HDC _HScreenDC;
public:
	HDC _HMemDc;
	BITMAP _BmpInfo;
	ReadType _Name;

	virtual bool  Init() noexcept override {  return true;}
	virtual bool Frame() override {  return true; }
	virtual bool Render()override {	return true;}
	bool Clear() noexcept override
	{
		DeleteObject(_HBitmap);
		ReleaseDC(world::HWnd, _HMemDc);
		return true;
	};


	bool Load(HDC ScreenHandle, const ReadType& Fullpath,
		const ReadType& filename) noexcept
	{
		// TODO :: DDB Device Dependency Bitmap ����̽� ������ ��Ʈ��
	// TODO :: DIB Device InDependency Bitmap ����̽� ������ ��Ʈ��
		_HScreenDC = ScreenHandle;

		if (_HBitmap = static_cast<HBITMAP>(LoadImage(world::HInstance,
			Fullpath.c_str(),
			IMAGE_BITMAP,
			0, 0,
			LR_DEFAULTSIZE | LR_LOADFROMFILE)))
		{
			_Name = filename;
		}
		else
		{
			return false;
		}

		GetObject(_HBitmap, sizeof(HBITMAP__), &_BmpInfo);

		_HMemDc =
			CreateCompatibleDC(_HScreenDC); 

		SelectObject(_HMemDc, _HBitmap);

		return true;
	}


	Bitmap()
	{
		Init();
	}
	~Bitmap() noexcept
	{
		Clear();
	}
	Bitmap(Bitmap&&) noexcept = default;
	Bitmap(const Bitmap&) = default;
	Bitmap& operator=(Bitmap&&) noexcept = default;
	Bitmap& operator=(const Bitmap&) = default;
};
