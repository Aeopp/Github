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
	Load(std::move(SharedScreenDC),std::move (  Fullpath ) );
}

Bitmap::~Bitmap()
{

}

bool Bitmap::Load(std::shared_ptr<HDC__> SharedScreenDC, tstring Fullpath)
{
	if (SharedScreenDC == nullptr)
		return false; 
	if (auto SharedWindowInstance = World::hInstance.lock();
		SharedWindowInstance)
	{
		ScreenHDC = SharedScreenDC;
		LoadDIB(SharedWindowInstance, SharedScreenDC, Fullpath);



		//Filename = Utility::PathDelete(Fullpath);
		//BitmapHandle = std::unique_ptr<HBITMAP__, decltype(ObjectDeleter)>((HBITMAP)LoadImage(SharedWindowInstance.get(),
		//	std::move(Fullpath.c_str()),
		//	IMAGE_BITMAP,
		//	0, 0,
		//	LR_DEFAULTSIZE | LR_LOADFROMFILE),
		//	ObjectDeleter);

		GetObject(BitmapHandle.get(), sizeof(BITMAP), &BmpInfomation);
		MemoryHDC = std::unique_ptr<HDC__, decltype(HDCReleaseDC)>(
		CreateCompatibleDC(SharedScreenDC.get()), HDCReleaseDC);
		SelectObject(MemoryHDC.get(), BitmapHandle.get());
	}
	else return false;
}

bool Bitmap::LoadDIB(std::shared_ptr<HINSTANCE__>SharedWindowInstance,std::shared_ptr<HDC__> SharedScreenDC, tstring Fullpath)
{
	HANDLE FileHandle = CreateFile(Fullpath.c_str(),
		GENERIC_READ,
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE) {
		return false;
	}
	unsigned long Read, DataSize;
	
		ReadFile(FileHandle, &BitFileHeader, sizeof(BITMAPFILEHEADER),
			&Read, NULL);
		DataSize = BitFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		BITMAPINFO* BitInfo = static_cast<BITMAPINFO*>(malloc(DataSize));
		ReadFile(FileHandle, BitInfo, DataSize, &Read, NULL);

		BitmapHandle = std::unique_ptr<HBITMAP__, decltype(ObjectDeleter)>(
			CreateDIBSection(
				SharedScreenDC.get(),
				BitInfo, DIB_RGB_COLORS,
				&Raster, NULL, 0), ObjectDeleter);

		unsigned long MaxSize = BitFileHeader.bfSize - BitFileHeader.bfOffBits;
		ReadFile(FileHandle, Raster, MaxSize, &Read, NULL);
	
	
		free(BitInfo);
		CloseHandle(FileHandle);
		return true; 
}
