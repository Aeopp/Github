#pragma once
#include "Actor.h"
class AHero :public Actor
{
public :
	using Actor::Actor; 

	 bool Frame() override;
	bool Init() noexcept override;
	bool Clear() noexcept override; 
	
	// Mesh �� �н��ϱ����� �������̽�
	
	AHero() = default;
	virtual ~AHero() noexcept;
};

