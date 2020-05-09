#pragma once
#include "Utility.h"
class Object
{
public:
	using Super = Object; 
public:
	virtual bool		Frame() = 0;
	virtual bool		Render() = 0;
public:
	Object() {}
	virtual ~Object() {}
	Object(const Object&) = default;
	Object&operator=(const Object&)=default;
	Object(Object&&)noexcept =default ;
	Object& operator=(Object&&)noexcept = default;
};

