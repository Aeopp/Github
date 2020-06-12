#pragma once
#include "Object.h"
#include <memory>
#include <vector>
#include "Mesh.h"



class Actor : public Object, public std::enable_shared_from_this<Actor>
{
private:
	std::shared_ptr<	class	Mesh> _Mesh{ nullptr };
	using Super = Object;
protected:
public:
	bool Init()override;
	bool Release()noexcept override;
	bool Frame(float DeltaTime)override;
	bool Render(float DeltaTime)override;

	void CreateMesh(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext, const std::wstring_view pTextureFileName, RECTANGLE rect);

	inline class std::shared_ptr<	class	Mesh> GetMesh() const&{
		return _Mesh;
	}
	inline void SetMesh(std::shared_ptr<	class	Mesh> Param)& {
		_Mesh = std::move(Param);
	};
public :
	FVector2 Position{ 0,0 };

	Actor();
	virtual ~Actor()noexcept;
};

