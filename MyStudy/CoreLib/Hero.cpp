#pragma once
#include "Hero.h"
#include "Input.h"
#include <functional>

bool AHero::Frame()
{
	_Mesh._RectDestination.left = _Mesh._PosX;
	_Mesh._RectDestination.top = _Mesh._PosY;
	return true;
};

template<typename binary_func,
	// 함수객체만 템플릿 파라미터로 허용.
	typename = binary_func::is_transparent>
	static constexpr auto _Move_Pos_Helper(float_t& _Mesh_Pos, const binary_func& Bi_func)
{
	return    [&_Mesh_Pos, &Bi_func]
	{
		_Mesh_Pos = Bi_func(_Mesh_Pos, static_cast<float_t>((time::delta_sec * 100.0f)));
	};
};

bool AHero::Init() noexcept
{
	using _Key = Input::EKeyState;

	// TODO :: Press or Hold 로 바꾸어야함
	// 사용자의 키 입력에 따라 메쉬의 포지션 좌표값을 조정해줍니다.
	util::GetInstance<Input>().Func_Regist({ 'W' }, { _Key::Hold, _Key::Press },
		_Move_Pos_Helper(_Mesh._PosY, std::minus<>{}));

	util::GetInstance<Input>().Func_Regist({ 'S' }, { _Key::Hold, _Key::Press },
		_Move_Pos_Helper(_Mesh._PosY, std::plus<>{}));

	util::GetInstance<Input>().Func_Regist({'A'
}, { _Key::Hold, _Key::Press },
		_Move_Pos_Helper(_Mesh._PosX, std::minus<>{}));

	util::GetInstance<Input>().Func_Regist({ 'D' }, { _Key::Hold, _Key::Press },
		_Move_Pos_Helper(_Mesh._PosX, std::plus<>{}));

	return true;
}
bool AHero::Clear() noexcept
{
	return true;
}
AHero::~AHero() noexcept
{
	Clear(); 
}
;
