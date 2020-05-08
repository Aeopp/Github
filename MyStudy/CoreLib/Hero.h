#pragma once
#include "Actor.h"
class AHero :public Actor
{
public :
	using Actor::Actor; 

	 bool Frame() override;
	bool Init() noexcept override;
	bool Clear() noexcept override; 
	
	// Mesh 에 패스하기위한 인터페이스
	
	AHero() = default;
	virtual ~AHero() noexcept;
};

