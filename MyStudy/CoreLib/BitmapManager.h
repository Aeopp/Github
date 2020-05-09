#pragma once
#include "BitmapManager.h"
#include "Bitmap.h"
#include "Type_Aliases.h"
#include <map>
#include <optional>

class BitmapManager : public manager_Interface<BitmapManager>{
public:
	using manager_Interface::manager_Interface;
public:
		bool Init() noexcept;
		bool Clear()noexcept;
		bool Frame();
		bool Render();
	
       std::weak_ptr<Bitmap> GetBitmap(const ReadType& _Key);
	   std::weak_ptr<Bitmap> Load(HDC _HScreenDC, ReadType FullPath);
public : 
	friend class std::unique_ptr<BitmapManager>;
	friend struct std::unique_ptr<BitmapManager>::deleter_type;
	friend class util;
	
	
	
	BitmapManager(const BitmapManager&) = delete;
	BitmapManager& operator=(const BitmapManager&) = delete;
	BitmapManager(BitmapManager&&) noexcept = delete;
	BitmapManager& operator=(BitmapManager&&) noexcept = delete;
private:
	std::map<ReadType, std::shared_ptr<Bitmap> > Map;
	const ReadType Path;
	
	BitmapManager(ReadType setDefaultPath = L"../../../Data/Bitmap/") :
		Path{ std::move(setDefaultPath) }
	{
		Init();
	};
	virtual ~BitmapManager() noexcept
	{
		Clear();
	}


};



inline bool BitmapManager::Init() noexcept
{
	return true;
};

inline bool BitmapManager::Clear() noexcept
{
	Map.clear();
	return true; 
};

inline bool BitmapManager::Frame()
{
	for (auto& [_key, _Bitmap] : Map)
		_Bitmap->Frame();

	return true;
};

inline bool BitmapManager::Render()
{
	for (auto& [_key, _Bitmap] : Map)
		_Bitmap->Render();

	return true;
};

inline std::weak_ptr<Bitmap> BitmapManager::GetBitmap(const ReadType& _Key)
{
	if (auto find_iter = Map.find(_Key);
		find_iter != std::end(Map))
	{
		return find_iter->second;
	}
	else
	{
		return std::weak_ptr<Bitmap>{};
	};
};

inline std::weak_ptr<Bitmap> BitmapManager::Load(HDC _HScreenDC, std::wstring FullPath)
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
			if (_bitmap->Load(_HScreenDC, FullPath, filename))
			{
				return Map.try_emplace(std::move(find_iter), std::move(filename),
					std::move(_bitmap))->second;
			}
		}
	}
	else
		return std::weak_ptr<Bitmap>{}; 
};

