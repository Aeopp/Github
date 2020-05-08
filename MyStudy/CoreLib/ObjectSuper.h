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
	// TODO :: ��� �޴� Ŭ������ ������ ��� ������ ����
	// using Object::Object ;
	virtual ~Object()  noexcept = default;
	Object() = default;
	Object(Object&&) noexcept = default;
	Object(const Object&) = default;
	Object& operator=(Object&&) noexcept = default;
	Object& operator=(const Object&) = default;
};



   

