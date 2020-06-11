#pragma once
#include "Std.h"

namespace Shader{
	#include "VS.shh"
	#include "PS.shh"
}
// POSITION COLOR UV
struct P3VERTEX {
	float x, y, z;  
	float r, g, b, a;
	float u, v;  
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
	ID3D11Buffer*		m_pVertexBuffer    =nullptr;
	ID3D11InputLayout* m_pVertexLayout	   =nullptr;
	ID3D11VertexShader* m_pVS			   =nullptr;
	ID3D11PixelShader* m_pPS			   =nullptr;
	ID3D11ShaderResourceView* m_pSRV		   =nullptr;
	ID3D11SamplerState* m_pSamplerState = nullptr;  
public:
	bool Create(
		ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		P3VERTEX* vertices,UINT iNumCount);

	bool Init();
	bool Frame();
	bool Render();
	bool Release();
};

