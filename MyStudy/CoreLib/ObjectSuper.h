#pragma once
class ObjectSuper
{
public:
	virtual bool Init()                              noexcept;
	virtual bool Clear()                               noexcept;
	virtual bool Frame();

	virtual ~ObjectSuper()  noexcept = default;
	ObjectSuper(ObjectSuper&&) noexcept = default;
	ObjectSuper(const ObjectSuper&) = default;
	ObjectSuper& operator=(ObjectSuper&&) noexcept = default;
	ObjectSuper& operator=(const ObjectSuper&) = default;
	
protected:
	using Super = ObjectSuper;
	ObjectSuper() = default;
};



   

