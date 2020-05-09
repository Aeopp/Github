#include "Bitmap.h"
bool	Bitmap::Frame()
{
	return true;
}
bool	Bitmap::Render()
{
	return true;
}

// DDB(DC):디바이스종속비트맵, DIB(독립비트맵)

Bitmap::Bitmap(HDC hScreenDC, tstring Fullpath)
{
	ScreenHDC = std::unique_ptr<HDC__, decltype(HDCDeleter)>(hScreenDC, HDCDeleter);
	Filename = Utility::PathDelete(Fullpath);
	BitmapHandle = std::unique_ptr<HBITMAP__, decltype(BitmapHandleDeleter)>((HBITMAP)LoadImage(World::InstanceHandle,
		std::move(Fullpath.c_str()),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE),
		BitmapHandleDeleter);
	GetObject(BitmapHandle.get(), sizeof(BITMAP), &BmpInfomation);
	MemoryHDC = std::unique_ptr<HDC__, decltype(HDCDeleter)>(
		CreateCompatibleDC(ScreenHDC.get()), HDCDeleter);

	SelectObject(MemoryHDC.get(), BitmapHandle.get());
}

Bitmap::~Bitmap()
{

}