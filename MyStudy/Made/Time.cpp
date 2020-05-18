#include "Time.h"

 bool Time::Update() & noexcept {
	 while (true) {
		 current_time = std::chrono::system_clock::now();
		 Delta = std::chrono::duration_cast<MiliSec>(current_time - prev_time);
		 if (Delta >= FramePerSecond) {
			 // Delta - FramePerSecond; 짜투리 시간
			 prev_time = current_time;
			 auto hdc = window::get_hdc().lock();
			 auto delta_print = window::format_text("Delta Time : ", Delta.count());
			 TextOut(hdc.get(), 100, 100, delta_print.c_str(), delta_print.size());
			 break;
		 }
		 else {
			 // 프레임 제한에 의해 다음 처리까지 남은 시간동안 재운다. 
			 std::this_thread::sleep_for((prev_time + Delta) - current_time);
		 }
	 }
	
	return true;
}
