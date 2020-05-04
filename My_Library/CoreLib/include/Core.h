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
	// ���۷����̱� ������ �ݵ�� �����ڿ��� �ʱ�ȭ
	SoundMgr& _Sound_Mgr;
	Input& _Input_Helper;
	
	void inline set_delay(uint32_t p_delay)&;
	virtual bool Frame() { return true;  }
	virtual bool Render() { return true; }
	virtual bool Init() { return true; }
	virtual bool Clear()noexcept {return true;}
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


