#include "Hero.h"
#include "InputManager.h"
bool Hero::Frame()
{
	if (GetInputManager.KeyCheck('W')==EKeyState::Push || 
		GetInputManager.KeyCheck('W') == EKeyState::Hold)
	{
		Vector[1]-= World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('S') == EKeyState::Push || 
		GetInputManager.KeyCheck('S') == EKeyState::Hold)
	{
		Vector[1] += World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('A') == EKeyState::Push ||
		GetInputManager.KeyCheck('A') == EKeyState::Hold)
	{
		Vector[0] -= World::FramePerSecond * Speed;
	}
	if (GetInputManager.KeyCheck('D') == EKeyState::Push ||
		GetInputManager.KeyCheck('D') == EKeyState::Hold)
	{
		Vector[0] += World::FramePerSecond * Speed;
	}
	SetPos(Vector[0],Vector[1]);
	return true;
}
bool Hero::Render(std::shared_ptr<HDC__> hOffScreenDC)
{
	auto SharedBitmapMask = BitmapMask.lock();
	if (auto SharedBitmap = BitmapPtr.lock();
		SharedBitmap)
	{
		if (SharedBitmapMask != nullptr)
		{
			BitBlt(hOffScreenDC.get(),
				RectDestnation.left,
				RectDestnation.top,
				RectDestnation.right,
				RectDestnation.bottom,
				SharedBitmapMask->MemoryHDC.get(),
				RectSource.left,
				RectSource.top, SRCAND);
			BitBlt(hOffScreenDC.get(),
				RectDestnation.left,
				RectDestnation.top,
				RectDestnation.right,
				RectDestnation.bottom,
				SharedBitmap->MemoryHDC.get(),
				RectSource.left,
				RectSource.top, SRCINVERT);
			BitBlt(hOffScreenDC.get(),
				RectDestnation.left,
				RectDestnation.top,
				RectDestnation.right,
				RectDestnation.bottom,
				SharedBitmapMask->MemoryHDC.get(),
				RectSource.left,
				RectSource.top, SRCINVERT);
		}
		else
		{
			//__imp_TransparentBlt 외부 기호(참조 위치 	
			// 컬러키 사용 블릿팅
			TransparentBlt(hOffScreenDC.get(),
				RectDestnation.left,
				RectDestnation.top,
				RectDestnation.right,
				RectDestnation.bottom,

				SharedBitmap->MemoryHDC.get(),
				RectSource.left,
				RectSource.top,
				RectDestnation.right,
				RectDestnation.bottom,

				RGB(000, 067, 171));
		}
		return true;
	}
};

Hero::Hero()
{
	Speed = 200.0f;
}
Hero::~Hero()
{

}