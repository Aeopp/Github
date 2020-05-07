#pragma once
#include <map>
#include <memory>
#include <string>
#include "manager_Interface.h"
#include "Bitmap.h"
#include "Util.h"


class BitmapManager : private manager_Interface<BitmapManager>
{
public:
	using Key_Type = std::wstring;
	using Sound_ptr = std::shared_ptr<Bitmap>;
	friend class std::unique_ptr<BitmapManager>;
	friend struct std::unique_ptr<BitmapManager>::deleter_type;
	friend class util;

	BitmapManager(const BitmapManager&) = delete;
	BitmapManager& operator=(const BitmapManager&) = delete;
	BitmapManager(BitmapManager&&) noexcept = delete;
	BitmapManager& operator=(BitmapManager&&) noexcept = delete;

	bool Load(Key_Type LoadName)noexcept(false);
	bool Clear()noexcept;
	bool Init()noexcept(false);
	bool Frame();
	bool Render();

	// ����ڴ� Sound ��ü ���� �������� ���Ѵ�.
	std::weak_ptr<Bitmap> getBitmap(const Key_Type& Param_key);

	// ��������� ��� ���� ������̴� ������ �����ְ� Key �� �ش��ϴ� ������ ���
	void play_sound(const Key_Type& Param_key)&;
	void play_effect(const const Key_Type& Param_key)&;
	bool pause(const Key_Type& Param_key)&;
	bool stop(const Key_Type& Param_key)&;
	bool Volume_Up(const Key_Type& Param_key)&;
	bool Volume_Down(const Key_Type& Param_key)&;
private:
	// ���� ���ǿ� �޼ҵ�
	typename BitmapManager::Sound_ptr get_sound_ptr(const Key_Type& Param_key)&;
	BitmapManager();
	virtual ~BitmapManager() noexcept;
	std::map</*const */Key_Type, Sound_ptr> Map;
	std::weak_ptr<BitmapManager> Current_Bgm;
	FMOD::System* F_System;
};