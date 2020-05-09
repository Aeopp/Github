#pragma once
#include "Actor.h"

class ANpc : public Actor
{
public:
	using Actor::Actor; 
	bool Frame()override; 

	ANpc();
	~ANpc() noexcept;
	ANpc(ANpc&&) noexcept = default;
	ANpc(const ANpc&) = default;
	
	ANpc& operator=(ANpc&&) noexcept = default;
	ANpc& operator=(const ANpc&) = default;
};

