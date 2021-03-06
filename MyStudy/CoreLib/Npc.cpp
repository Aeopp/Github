#pragma once
#include "Npc.h"
#include <algorithm>

	static constexpr auto _Move_Pos_Helper(
	float_t& _Mesh_Pos,
	LONG& compare_Lhs, LONG& compare_Rhs,
	float_t& _Dir_Speed)
{	
	return  [&]
	{
		if (_Mesh_Pos < compare_Lhs || compare_Rhs < _Mesh_Pos)
			_Dir_Speed *= -1.f;
	};
};

bool ANpc::Frame()
{
	auto& _PosX = _Mesh._PosX;
	auto& _PosY = _Mesh._PosY;
	auto& [_worldleft,_worldtop, _worldright,_worldbottom] = world::RectClient;

	static auto Ping = 
	_Move_Pos_Helper(_PosY, _worldtop, _worldbottom, DirY);
	static auto Pong = 
	_Move_Pos_Helper(_PosX, _worldleft, _worldright, DirX);

	Ping();
	Pong();

	const auto _delta_sec = time::delta_sec;

	_Mesh._RectDestination.top=
		_PosY = std::clamp<float_t>
	(	_PosY + (DirY* _delta_sec * Speed), 
		_worldtop, _worldbottom);
	
	_Mesh._RectDestination.left = 
		_PosX = 
		std::clamp<float_t>
	(	_PosX + (DirX * _delta_sec * Speed),
		_worldleft, _worldright);
	
	return true; 
}

ANpc::ANpc()
{
	Speed = 100.f; 
}

ANpc::~ANpc() noexcept
{
	Clear();
	
}
