#pragma once
#include "MyWindow.h"
#include "manager_Interface.h"
#include "SoundMgr.h"
#include "Timer.h"
#include "Input.h"
#include "Dependency.h"
class Core : public MyWindow, manager_Interface<Core>
{
public:
	Timer _Timer;
	// 레퍼런스이기 때문에 반드시 생성자에서 초기화
	SoundMgr& _Sound_Mgr;
	Input& _Input_Helper;
	
	HFONT_ptr _HFont;
	HBRUSH_ptr _HBrush;
	HDC_ptr _HScreenDC;
	HDC_ptr _HOffScreenDC;
	HBITMAP_ptr _HOffScreenBitmap;
	
	void inline set_delay(uint32_t p_delay)&;
	bool Frame_Implementation()              { return true; };
	bool Render_Implementation()             { return true; };
	bool Init_Implementation()   noexcept;
	bool Clear_Implementation()noexcept      { return true; };
	
    bool Run()&;
	
	Core();
	std::chrono::milliseconds Delay;
	virtual ~Core() noexcept override;
protected:
	using Super = Core;
private:
	Core(const Core&) = delete;
	Core& operator=(const Core&) = delete;
	Core(Core&&) noexcept = delete;
	Core& operator=(Core&&) noexcept = delete;
	
	bool Core_Init()noexcept;
	bool Core_Clear()noexcept;
	bool Core_Frame();
	bool Core_Render();
};

void inline Core::set_delay(uint32_t p_delay)&
{
	Delay = static_cast<std::chrono::milliseconds>(p_delay);
} 

bool inline Core::Init_Implementation()   noexcept
{
	
}