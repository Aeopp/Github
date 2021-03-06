#pragma once
class ObjectSuper
{
public:
	virtual bool Init() noexcept= 0;
	virtual bool Render() const = 0;
	virtual bool Clear() noexcept= 0; 
	virtual bool Frame()  = 0;

	virtual ~ObjectSuper()  noexcept = default;
	ObjectSuper(ObjectSuper&&) noexcept = default;
	ObjectSuper(const ObjectSuper&) = default;
	ObjectSuper& operator=(ObjectSuper&&) noexcept = default;
	ObjectSuper& operator=(const ObjectSuper&) = default;
	
protected:
	using Super = ObjectSuper;
	ObjectSuper() = default;
};



   

