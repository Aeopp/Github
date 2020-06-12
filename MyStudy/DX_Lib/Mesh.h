#pragma once
#include "Std.h"
#include <vector>
#include <array>
<<<<<<< HEAD
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
=======

namespace Shader {
#include "VS.shh"
#include "PS.shh"
};

// POSITION COLOR UV
struct P3VERTEX {
	float x, y, z;  
	static inline constexpr UINT POSITION = sizeof(float) * 3;
	float r, g, b, a;
	static inline constexpr UINT COLOR = sizeof(float) * 4;
	float u, v;
	static inline constexpr UINT UV = sizeof(float) * 2;
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
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
	// ��ü ������ �ݵ�� �ʱ�ȭ
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	std::vector<PCT_VERTEX> m_pVertexList{};
	// ------------------------------------------
public:
<<<<<<< HEAD
	static constexpr UINT VertexNumber = 6;

=======
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
	ID3D11Buffer* m_pVertexBuffer = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11VertexShader* m_pVS = nullptr;
	ID3D11PixelShader* m_pPS = nullptr;
	ID3D11ShaderResourceView* m_pSRV = nullptr;
	ID3D11SamplerState* m_pSamplerState = nullptr;
<<<<<<< HEAD

	class Actor* Owner = nullptr;
	RECTANGLE RenderRect{ 0,0,0,0 };
=======
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
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
<<<<<<< HEAD
		RECTANGLE rect, Actor* Owner);
=======
		P3VERTEX* vertices, UINT iNumCount);
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
	bool Init();
	bool Frame(float DeltaTime);
	bool Render(float DeltaTime);
	bool Release();
private: 
<<<<<<< HEAD
	void OwnerPositionTORenderRECT()&;
=======
>>>>>>> parent of 7fb459c... Revert "텍스처 이미지 띄우는데까지 구현"
	virtual bool _CreateSamplerState()&;
};
