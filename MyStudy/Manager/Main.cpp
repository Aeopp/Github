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
	const std::wstring _key1 = L"../../Sound/romance.mid";
	const std::wstring _key2 = L"../../Sound/MyLove.mp3";
	const std::wstring _key3 = L"../../Sound/GunShot.mp3";
	
	Sound_Manager.Load(_key1);
	Sound_Manager.Load(_key2);
	Sound_Manager.Load(_key3);

	const auto BGM = Sound_Manager.getSound(_key1);
	if(auto bgm_play  = BGM.lock())
		bgm_play->Play(); 

	using std::bind;
	using std::ref;

	// weak_ptr -> shared_ptr  Input Manager 도 Sound 수명에 관여함
	// 필요없어진 함수를 지워야 Sound 객체도 사라짐
	Input_Manager.Func_Regist('1', _KEY::Press, &Sound::Play, Sound_Manager.getSound(_key1).lock());
	
	Input_Manager.Func_Regist('2', _KEY::Press, &Sound::Play, Sound_Manager.getSound(_key2).lock());

	Input_Manager.Func_Regist('3', _KEY::Press, &Sound::PlayEffect, Sound_Manager.getSound(_key3).lock());
	
	Input_Manager.Func_Regist('P', _KEY::Press, &Sound::Pause, BGM.lock());

	Input_Manager.Func_Regist(0x24, _KEY::Hold,
		&Sound::Volume_Up, BGM.lock());

	Input_Manager.Func_Regist(0x23, _KEY::Hold,
		&Sound::Volume_Down, BGM.lock());

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