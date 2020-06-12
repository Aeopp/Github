#pragma once
#include "Std.h"
#include <vector>
#include <array>
#include "Math.h"

namespace Shader {
	#include "VS.shh"
	#include "PS.shh"
};

// POSITION COLOR UV
struct PCT_VERTEX {
	FVector3 p;
	FVector4 c;
	FVector2 t;

	static inline constexpr UINT POSITION = sizeof(decltype(p));
	static inline constexpr UINT COLOR = sizeof(decltype(c));
	static inline constexpr UINT UV = sizeof(decltype(t));
};

class Mesh
{
public:
	Mesh() = default;
	Mesh& operator=(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh(const Mesh&) = delete;
public:
	// 객체 생성시 반드시 초기화
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	std::vector<PCT_VERTEX> m_pVertexList{};
	// ------------------------------------------
public:
	static constexpr UINT VertexNumber = 6;

	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;
	ID3D11ShaderResourceView* m_pSRV = nullptr;
	ID3D11SamplerState* m_pSamplerState = nullptr;

	class Actor* Owner = nullptr;
	RECTANGLE RenderRect{ 0,0,0,0 };
public:
	inline class Actor* GetOwner() & noexcept {
		return Owner;
	};
	inline void SetOwner(class Actor* Param) & noexcept {
		Owner = Param;
	};
	bool Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		const std::wstring_view pTextureFileName,
		RECTANGLE rect, Actor* Owner);
	bool Init();
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);
	bool Release();
private: 
	void OwnerPositionTORenderRECT()&;
	virtual bool _CreateSamplerState()&;
};
