#include "Mesh.h"
#include "BitmapManager.h"
bool Mesh::Load( HDC_ptr Arg_HDC, const std::wstring& FileName)
{
	// TODO :: ��Ʈ�� �Ŵ������� �ε��� ��û�Ѵ�.
	// TODO :: �޽��� ��Ʈ���� �������� �ʴ´�.
	// TODO :: �޽��� �����ͷ� ��ȯ
	if (auto bitmap_ptr = util::GetInstance<BitmapManager>().Load(Arg_HDC, FileName);
		bitmap_ptr)
	{
		_Bitmap = std::move(bitmap_ptr);
	}
	else
		return false; 

	auto& [_Srcleft, _Srctop, _Srcright, _Srcbottom] = _RectSource;
	auto& [_Destleft, _Desttop, _Destright, _Destbottom] = _RectDestination;
	auto& [_worldleft, _worldtop, _worldright, _worldbottom] = world::RectClient;

	_Srctop = _Srcleft = 0;
	
	_Srcright = _Bitmap->_BmpInfo.bmWidth;
	_Srcbottom = _Bitmap->_BmpInfo.bmHeight;

	_Desttop = _Destleft = 0;

	_Destright = _worldright - _worldleft;
	_Destbottom = _worldbottom - _worldtop;

	_PosX = _PosY = 0;

	return true;
};
 
bool Mesh::Render(HDC_ptr hOffScreenDC) const
{
	const auto& _Dest = _RectDestination;
	const auto& _Src = _RectSource;
	
	BitBlt(hOffScreenDC.get(),
		_Dest.left,
		_Dest.top,
		_Dest.right,
		_Dest.bottom,
		_Bitmap->_HMemDc.get(),
		_Src.top,
		_Src.top, SRCCOPY);

	return true; 
}


