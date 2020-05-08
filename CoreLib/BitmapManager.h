#pragma once
#include "Bitmap.h"
#include "Type_Aliases.h"
#include <map>
#include <optional>

class BitmapManager : public manager_Interface<BitmapManager>{
public:
	using Bitmap_ptr = std::shared_ptr<Bitmap>;

public:
		bool Init_Implementation() noexcept;
		bool Clear_Implementation()noexcept;
		bool Frame_Implementation();
		bool Render_Implementation();

	
	
		Bitmap_ptr GetPtr(const ReadType& _Key);
		typename BitmapManager::Bitmap_ptr Load(HDC_ptr _HScreenDC, std::wstring FullPath);
public : 
	friend class std::unique_ptr<BitmapManager>;
	friend struct std::unique_ptr<BitmapManager>::deleter_type;
	friend class util;

	BitmapManager(const BitmapManager&) = delete;
	BitmapManager& operator=(const BitmapManager&) = delete;
	BitmapManager(BitmapManager&&) noexcept = delete;
	BitmapManager& operator=(BitmapManager&&) noexcept = delete;
private:
	std::map<std::wstring, Bitmap_ptr> Map;
	const ReadType Path;
	BitmapManager(std::wstring setDefaultPath = L"../../../Bitmap/");
	virtual ~BitmapManager()noexcept; 
};

BitmapManager::BitmapManager(ReadType setDefaultPath ) :
	Path{ std::move(setDefaultPath) }
{
	Init_Implementation(); 
};

inline bool BitmapManager::Init_Implementation() noexcept
{
	return true;
};

inline bool BitmapManager::Clear_Implementation() noexcept
{
	Map.clear();
};

inline bool BitmapManager::Frame_Implementation()
{
	for (auto& [_key, _Bitmap] : Map)
		_Bitmap->Frame();

	return true;
};

inline bool BitmapManager::Render_Implementation()
{
	for (auto& [_key, _Bitmap] : Map)
		_Bitmap->Render();

	return true;
};

inline BitmapManager::Bitmap_ptr BitmapManager::GetPtr(const ReadType& _Key)
{
	if (auto find_iter = Map.find(_Key);
		find_iter != std::end(Map))
	{
		return find_iter->second;
	}
	else
	{
		return typename::BitmapManager::Bitmap_ptr{};
	};
};

inline BitmapManager::Bitmap_ptr BitmapManager::Load(HDC_ptr _HScreenDC, std::wstring FullPath)
{
	// ../../../data/path/filename.mp3 -> filename.mp3
	// 문자열이 올바른 경로인지는 검사하지 않는다.
	auto filename = File::PathDelete(FullPath);

	if (auto find_iter = Map.lower_bound(filename);
		find_iter != std::end(Map) || find_iter->first > filename)
	{
		// 데이터가 없으니 로딩
		if (auto _bitmap = std::make_shared<Bitmap>();
			_bitmap->Init())
		{
			if (_bitmap->Load(std::move(_HScreenDC), FullPath, filename))
			{
				return Map.try_emplace(std::move(find_iter), std::move(filename),
					std::move(_bitmap))->second;
			}
		}
	}
	else
		return typename BitmapManager::Bitmap_ptr{};
};

inline BitmapManager::~BitmapManager() noexcept
{
	Clear_Implementation(); 
}
