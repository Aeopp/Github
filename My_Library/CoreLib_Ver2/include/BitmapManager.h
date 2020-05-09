#pragma once
#include "Bitmap.h"
class BitmapManager : public SingleTon<BitmapManager>
{
	friend class SingleTon<BitmapManager>;
private:
	std::map<tstring,std::shared_ptr<Bitmap>>  Bitmaps;
public:
	const tstring					DefaultPath;
public:
	bool	Frame();
	bool	Render();
	std::weak_ptr<Bitmap>		Load(HDC ScreenDCHandle,tstring FullPath);
	std::weak_ptr<Bitmap> GetBitmap(tstring Key);
private:
	BitmapManager();
public:
	~BitmapManager()noexcept;
	DELETE_MOVE_COPY(BitmapManager)
};

#define GetBitmapManager BitmapManager::Instance()