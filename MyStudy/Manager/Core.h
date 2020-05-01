#pragma once
#include "SoundMgr.h"
#include "Timer.h"
#include "Input.h"

class Core : manager_Interface<Core>
{
public:
	Timer _Timer;
	// 레퍼런스이기 때문에 반드시 생성자에서 초기화
	SoundMgr& _Sound_Mgr;
	Input& _Input_Helper;
	bool isExit;

	void inline set_delay(uint32_t p_delay)&;
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Init()= 0;
	virtual bool Clear() noexcept= 0;;
    bool Run()&;
	
	Core();
	virtual ~Core() noexcept override;
protected:
	using Super = Core;
private:
	std::chrono::milliseconds Delay; 
	
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


