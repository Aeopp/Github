#pragma once
#include "Actor.h"
class AHero :public Actor
{
public :
	virtual bool Frame() override;
	virtual bool Init() noexcept override;

	// Mesh �� �н��ϱ����� �������̽�
	
	AHero() = default;
};

