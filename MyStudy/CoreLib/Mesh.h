#pragma once
#include "ObjectSuper.h"
#include "BitmapManager.h"
#include <type_traits>
class Mesh : public Object{
private:
	std::weak_ptr<Bitmap> _Bitmap;
	RECT _RectSource;
public :
	float_t _PosX;
	float_t _PosY;
	RECT _RectDestination;

	Mesh() = default;
	virtual ~Mesh() noexcept;

	template<typename _RECT,
	typename = std::enable_if_t<std::is_same_v<std::decay_t<_RECT>,RECT>,int>>
	void inline SetRect(_RECT&& Arg_RectSource, _RECT&& Arg_RectDestination)noexcept;
	
	bool Load(HDC Arg_HDC, const std::wstring& FileName);
	bool Render(HDC hOffScreenDC)const;
	bool inline Clear()noexcept override  ;
};

Mesh::~Mesh() noexcept
{
	Mesh::Clear();
};

template <typename _RECT, typename>
void inline Mesh::SetRect(_RECT&& Arg_RectSource, _RECT&& Arg_RectDestination) noexcept
{
	_RectSource = std::forward< _RECT>(Arg_RectSource);
	_RectDestination = std::forward<_RECT>(Arg_RectDestination);

	_PosX = _RectDestination.left;
	_PosY = _RectDestination.top;
};

bool inline Mesh::Clear() noexcept
{
	return true; 
}

