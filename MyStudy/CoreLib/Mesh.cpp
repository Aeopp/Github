#include "Mesh.h"

Mesh::~Mesh() noexcept
{
	Clear();
}

bool Mesh::Load(/*const*/ HDC_ptr/*&*/ Arg_HDC, const std::wstring& FileName)
{
	_Bitmap.Load(Arg_HDC, FileName);

	auto& [_Srcleft, _Srctop, _Srcright, _Srcbottom] = _RectSource;
	auto& [_Destleft, _Desttop, _Destright, _Destbottom] = _RectDestination;
	auto& [_worldleft, _worldtop, _worldright, _worldbottom] = world::RectClient;

	_Srctop = _Srcleft = 0;

	_Srcright = _Bitmap._BmpInfo.bmWidth;
	_Srcbottom = _Bitmap._BmpInfo.bmHeight;

	_Desttop = _Destleft = 0;

	_Destright = _worldright - _worldleft;
	_Destbottom = _worldbottom - _worldtop;

	_PosX = _PosY = 0;

	return true;
};
 
bool Mesh::Render(/*const*/ HDC_ptr/*&*/ hOffScreenDC) const
{
	const auto& _Dest = _RectDestination;
	const auto& _Src = _RectSource;
	
	BitBlt(hOffScreenDC.get(),
		_Dest.left,
		_Dest.top,
		_Dest.right,
		_Dest.bottom,
		_Bitmap._HMemDc.get(),
		_Src.top,
		_Src.top, SRCCOPY);

	return true; 
}

bool Mesh::Init() noexcept
{
	return true; 
}



bool Mesh::Clear() noexcept
{
	return _Bitmap.Clear();
}

bool Mesh::Frame()
{
	return true; 
}


