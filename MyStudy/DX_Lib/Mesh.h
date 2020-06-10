#pragma once
#include "Std.h"
struct P3VERTEX {
	float x, y, z;
	float r, g, b, a;
};
class Mesh
{
public :
	Mesh() = default;  
	Mesh& operator=(const Mesh&) = delete;
	Mesh& operator=(Mesh&&) = delete;
	Mesh(Mesh&&) = delete;
	Mesh(const Mesh&) = delete;
public:
	// 객체 생성시 반드시 초기화
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	P3VERTEX* m_pVertexList = nullptr;
	// ------------------------------------------
	UINT m_iNumVertex;
public:
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVS;
	ID3D11PixelShader* m_pPS;
public:
	bool Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		P3VERTEX* vertices,
		UINT iNumCount
	);
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

