#include "SoundMgr.h"
#include "Timer.h"
#include "Util.h"
#include "Input.h"
//#include <WinUser.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std::literals::chrono_literals; 

int main() {
	// std::invoke(foo, 1, 2, 3);
	constexpr std::chrono::milliseconds Delay = 15ms;
	using _KEY = typename Input::EKey;
	
	// unique-ptr Ref 
	Timer LocalTimer;
	auto& Input_Manager = util::GetInstance<Input>();
	auto& Sound_Manager = util::GetInstance<SoundMgr>();

	LocalTimer.Init();
	Input_Manager.Init();
	Sound_Manager.Init();

	// 소스파일 폴더위치기준
	std::wstring _key1 = L"../../Sound/romance.mid";
	std::wstring _key2 = L"../../Sound/MyLove.mp3";
	std::wstring _key3 = L"../../Sound/GunShot.mp3";
	
	Sound_Manager.Load(_key1);
	Sound_Manager.Load(_key2);
	Sound_Manager.Load(_key3);

	auto BGM = Sound_Manager.getSound(_key1);
	BGM->Play();

	using std::bind;
	using std::ref;

	Input_Manager.Func_Regist(bind(&Sound::Play,Sound_Manager.getSound(_key1)),
	'1', _KEY::Press);

	Input_Manager.Func_Regist(bind(&Sound::Play, Sound_Manager.getSound(_key2)),
		'2', _KEY::Press);

	Input_Manager.Func_Regist(
		bind(&Sound::PlayEffect, Sound_Manager.getSound(_key3)),'3', _KEY::Press);
	
	Input_Manager.Func_Regist(
		bind(&Sound::Pause,BGM),'P', _KEY::Press);

	Input_Manager.Func_Regist(
		bind(&Sound::Volume_Up, BGM), 0x24, _KEY::Hold);

	Input_Manager.Func_Regist(
	bind(&Sound::Volume_Down, BGM), 0x23, _KEY::Hold);

	while (true) {
		LocalTimer.Frame();
		Sound_Manager.Frame();
		Input_Manager.Frame();
		
		LocalTimer.Render();
		Sound_Manager.Render();
		Input_Manager.Render();
		// 슬립으로 프레임 조절
		std::this_thread::sleep_for(Delay);
	};
}