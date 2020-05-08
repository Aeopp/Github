#pragma once
#include <utility>

class Object
{
public:
	virtual bool Init()noexcept
	{
		return true; 
	}
	virtual bool Clear()noexcept
	{
		return true;
	}

	virtual bool Frame()
	{
		return true;
	}

	virtual bool Render()
	{
		return true;
	}
protected:
	// TODO :: 상속 받는 클래스들 생성자 상속 받으면 편함
	// using Object::Object ;
	virtual ~Object()  noexcept = default;
	Object() = default;
	Object(Object&&) noexcept = default;
	Object(const Object&) = default;
	Object& operator=(Object&&) noexcept = default;
	Object& operator=(const Object&) = default;
};



   

