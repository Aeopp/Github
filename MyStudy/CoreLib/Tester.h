#pragma once
#include "Core.h"

class Tester : public Core
{
protected: 
	virtual bool Frame()override; 
	virtual bool Render()override;
	virtual bool Init() override;
	virtual bool Clear()noexcept override;
};

