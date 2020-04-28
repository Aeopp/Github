#pragma once
#include "ObjectSuper.h"
#include <string>
class Sound : public ObjectSuper 
{
public:
	using ReadType = std::wstring; 

	virtual bool Init()noexcept override;
	virtual bool Render() const override;
	virtual bool Clear()noexcept override;
	virtual bool Frame() override;

	virtual ~Sound() = default;
	Sound() = default; 

	bool Load(ReadType Param);
	bool Play()const; 
private:
	ReadType Name;
};

