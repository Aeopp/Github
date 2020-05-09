#pragma once
#include "Utility.h"
class TBaseObject
{
public:
	virtual bool		Init() = 0;
	virtual bool		Frame() = 0;
	virtual bool		Render() = 0;
	virtual bool		Release() = 0;
public:
	TBaseObject() {}
	virtual ~TBaseObject() {}
};

