#pragma once
#include <memory>
#include <string_view>


//template<typename SubClass>

class Object abstract/*: std::enable_shared_from_this<SubClass>*/
{
public:	
	friend class World;
public:
virtual	bool Init()abstract;
virtual	bool Release()noexcept abstract;
virtual bool Frame(float DeltaTime) abstract;
virtual bool Render(float DeltaTime)abstract;
public :
	std::wstring_view Tag{};

	inline  std::wstring_view  GetTag() const& {
		return Tag;
	}
	inline void SetTag(std::wstring_view Param)& {
		Tag = Param;
	}

	template<typename ObjectSubClassType>
	static std::shared_ptr<ObjectSubClassType> CreateObject() {
		return std::shared_ptr<ObjectSubClassType>();
	};

	Object&operator=(const Object&) = delete;
	Object&operator=(Object&&) = delete;
	Object(Object&&) = delete;
	Object(const Object&) = delete;
	virtual ~Object()noexcept;
	Object();
private:
};


