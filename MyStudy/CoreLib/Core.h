#pragma once
#include "MyWindow.h"
#include "manager_Interface.h"
#include "SoundMgr.h"
#include "Timer.h"
#include "Input.h"
#include "Dependency.h"
#include "BitmapManager.h"

class Core : public MyWindow, manager_Interface<Core>
{
public:
	using Super = Core;
	
	Timer _Timer;
	// ���۷����̱� ������ �ݵ�� �����ڿ��� �ʱ�ȭ
	SoundMgr& _Sound_Mgr;
	Input& _Input_Helper;
	BitmapManager& _BitmapManager;

	HFONT_ptr _HDefaultFont; 
	HFONT_ptr _HFont;
	HBRUSH_ptr _HBrushBackGround;
	HDC_ptr _HScreenDC;
	HDC_ptr _HOffScreenDC;
	HBITMAP_ptr _HOffScreenBitmap;
	
	void inline set_delay(uint32_t p_delay)&;

	bool Frame_Implementation();
	bool Render_Implementation();
	bool Init_Implementation()   noexcept; 
	bool Clear_Implementation()noexcept;

	bool PreRender();
	bool PostRender();
	// TODO :: Core ���� �Լ��� ������ �ϰ� �θ��� �Լ��� �ݵ�� �������� �θ���
	virtual bool Frame() = 0;
	virtual bool Render() = 0;
	virtual bool Init()   noexcept = 0;
	virtual bool Clear()noexcept = 0;
	
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
};

void inline Core::set_delay(uint32_t p_delay)&
{
	Delay = static_cast<std::chrono::milliseconds>(p_delay);
} 
