#include "Mesh.h"
#include "BitmapManager.h"
#include <chrono>


bool Mesh::Load( HDC Arg_HDC, const std::wstring& FileName)
{
	// TODO :: 비트맵 매니저에게 로딩을 요청한다.
	// TODO :: 메쉬는 비트맵을 소유하지 않는다.
	// TODO :: 메쉬를 포인터로 전환
	if (auto bitmap_ptr = util::GetInstance<BitmapManager>().Load(Arg_HDC, FileName).lock();
		bitmap_ptr)
	{
		_Bitmap =  bitmap_ptr;

		auto& [_Srcleft, _Srctop, _Srcright, _Srcbottom] = _RectSource;
		auto& [_Destleft, _Desttop, _Destright, _Destbottom] = _RectDestination;
		auto& [_worldleft, _worldtop, _worldright, _worldbottom] = world::RectClient;

		_Srctop = _Srcleft = 0;

		_Srcright = bitmap_ptr->_BmpInfo.bmWidth;
		_Srcbottom = bitmap_ptr->_BmpInfo.bmHeight;

		_Desttop = _Destleft = 0;

		_Destright = _worldright - _worldleft;
		_Destbottom = _worldbottom - _worldtop;

		_PosX = _PosY = 0;
	}
	else
		return false; 


	

	return true;
};
 
bool Mesh::Render(HDC hOffScreenDC) const
{
	const auto& _Dest = _RectDestination;
	const auto& _Src = _RectSource;

	if (auto _BitmapShared = _Bitmap.lock();
		_BitmapShared) {

		BitBlt(hOffScreenDC,
			_Dest.left,
			_Dest.top,
			_Dest.right,
			_Dest.bottom,
			_BitmapShared->_HMemDc,
			_Src.top,
			_Src.top, SRCCOPY);

		return true;
	}
	else 
		return false; 
}


