#include "SoundMgr.h"
#include "Timer.h"
#include "Util.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::literals::chrono_literals; 

int main() {
	

	// unique-ptr Ref 
	 auto& Sound_Manager = util::GetInstance<SoundMgr>();

	// SoundMgr* Sound_Manager = new SoundMgr;

	std::wstring _key1 = L"0.mp3"; 
	std::wstring _key2 = L"1.wav"; 
	std::wstring _key3 = L"2.mid"; 
	
	Sound_Manager.Load(_key1);
	Sound_Manager.Load(_key2);
	Sound_Manager.Load(_key3);

	auto Local_Sound = Sound_Manager.getSoundPtr(_key1); 
	Local_Sound->Play(); 

	Timer LocalTimer;
	LocalTimer.Init();

	while (true /*디버깅용 */    /*LocalTimer.FrameTime < 10.f*/) {
		LocalTimer.Frame();
		LocalTimer.Render();

		// 슬립으로 프레임 조절
		std::this_thread::sleep_for(1ms);
	};
	LocalTimer.Clear(); 
}