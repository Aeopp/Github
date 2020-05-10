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
Bitmap::Bitmap(std::shared_ptr<HDC__> SharedScreenDC, tstring Fullpath)
{
	if (SharedScreenDC== nullptr)
		throw std::exception(Debug::Log("ScreenDC Invalid !! "));
	if (auto SharedWindowInstance = World::InstanceHandle.lock();
		SharedWindowInstance)
	{
		ScreenHDC = SharedScreenDC;

		Filename = Utility::PathDelete(Fullpath);
		BitmapHandle = std::unique_ptr<HBITMAP__, decltype(ObjectDeleter)>((HBITMAP)LoadImage(SharedWindowInstance.get(),
			std::move(Fullpath.c_str()),
			IMAGE_BITMAP,
			0, 0,
			LR_DEFAULTSIZE | LR_LOADFROMFILE),
			ObjectDeleter);
		GetObject(BitmapHandle.get(), sizeof(BITMAP), &BmpInfomation);
		MemoryHDC = std::unique_ptr<HDC__, decltype(HDCDeleteDC)>(
			CreateCompatibleDC(SharedScreenDC.get()), HDCDeleteDC);

		SelectObject(MemoryHDC.get(), BitmapHandle.get());
	}
	else throw std::exception(Debug::Log("WindowInstance Invalid!! ")); 
}

Bitmap::~Bitmap()
{

}