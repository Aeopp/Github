#pragma once
#include "Actor.h"

class ANpc : public Actor
{
	float_t _DirX_Speed;
	float_t _DirY_Speed;
	const float_t speed;
public:
	bool Frame() override;
	
	ANpc();
	~ANpc() noexcept = default;
	ANpc(ANpc&&) noexcept = default;
	ANpc(const ANpc&) = default;
	
	ANpc& operator=(ANpc&&) noexcept = default;
	ANpc& operator=(const ANpc&) = default;
};

