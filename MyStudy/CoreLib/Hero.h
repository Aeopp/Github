#pragma once
#include "Actor.h"
class AHero :public Actor
{
public :
	virtual bool Frame() override;
	virtual bool Init() noexcept override;

	// Mesh 에 패스하기위한 인터페이스
	
	AHero() = default;
};

