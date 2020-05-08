#pragma once
#include <utility>

class ObjectSuper
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
	virtual ~ObjectSuper()  noexcept = default;
	ObjectSuper() = default;
	ObjectSuper(ObjectSuper&&) noexcept = default;
	ObjectSuper(const ObjectSuper&) = default;
	ObjectSuper& operator=(ObjectSuper&&) noexcept = default;
	ObjectSuper& operator=(const ObjectSuper&) = default;
};



   

