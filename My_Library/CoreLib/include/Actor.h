#pragma once
#include "ObjectSuper.h"
#include "Mesh.h"
class Actor :
	public Object
{
public:
	using Super = Actor;
	Mesh _Mesh;
	virtual ~Actor() noexcept = default;
	Actor() = default;
	Actor(Actor&&) noexcept = default;
	Actor(const Actor&) = default;
	Actor& operator=(Actor&&) noexcept = default;
	Actor& operator=(const Actor&) = default;

	virtual bool Render() {
		return true;
	};
	virtual bool Frame() {
		return true;
	};
	virtual bool Init() noexcept{
		return true;
	};
	virtual bool Clear() noexcept {
		return true;
	};


	//virtual bool Load(const HDC& Arg_HDC, const std::wstring& FileName)
	//{
	//	return std::invoke(&Mesh::Load, std::ref(_Mesh), Arg_HDC, FileName);
	//}
	//virtual bool SetRect(const HDC& Arg_HDC, const std::wstring& FileName)
	//{
	//	return std::invoke(&Mesh::Load, std::ref(_Mesh), Arg_HDC, FileName);
	//}
private:
};

