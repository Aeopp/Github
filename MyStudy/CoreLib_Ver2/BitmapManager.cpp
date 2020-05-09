#include "BitmapManager.h"

bool	BitmapManager::Frame()
{
	for (auto& [Key, Bitmap] : Bitmaps) {
		Bitmap->Frame();
	}
	return true;
}
bool	BitmapManager::Render()
{
	for (auto&[Key,Bitmap] : Bitmaps) {
		Bitmap->Render();
	}
	return true;
}


std::weak_ptr<Bitmap>	BitmapManager::Load(HDC ScreenDCHandle, tstring FullPath)
{
	// ../../../data/sound/xx.mp3
	tstring FileName = Utility::PathDelete(FullPath);
	if (auto FindIterator = Bitmaps.lower_bound(FileName);
		FindIterator != std::end(Bitmaps) && FindIterator->first == FileName) {
		return FindIterator->second;
	}
	else if (auto NewBitmap = std::make_shared<Bitmap>(Bitmap(ScreenDCHandle, FullPath));
		NewBitmap) {
		return Bitmaps.try_emplace(FindIterator, std::move(FileName), std::move(NewBitmap))->second;
	}
}

std::weak_ptr<Bitmap> BitmapManager::GetBitmap(tstring Key)
{
	if (auto FindIterator = Bitmaps.find(Key);
		FindIterator != std::end(Bitmaps)) {
		return FindIterator->second;
	}
	else return {};
}
BitmapManager::~BitmapManager()noexcept {};
BitmapManager::BitmapManager():
	DefaultPath{ L"../../../Data/Bitmap/" }
{};