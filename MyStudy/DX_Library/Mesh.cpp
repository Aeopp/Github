#include "Mesh.h"
#include "Math.h"
#include "Actor.h"

bool Mesh::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,
	const std::wstring_view pTextureFileName,
	RECTANGLE rect,
	Actor* Owner) {

	SetOwner(Owner);
	RenderRect = rect;
	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;

	m_pVertexList.reserve(Mesh::VertexNumber);

	m_pVertexList[0].p = Math::ScreenToNDC({ rect.left, rect.top });
	m_pVertexList[0].t = { 0.f, 0.f };

	m_pVertexList[1].p = Math::ScreenToNDC({ rect.right, rect.top });
	m_pVertexList[1].t = { 1, 0 };

	m_pVertexList[2].p = Math::ScreenToNDC({ rect.left, rect.bottom });
	m_pVertexList[2].t = {0, 1 };

	m_pVertexList[3].p = Math::ScreenToNDC({ rect.left, rect.bottom });
	m_pVertexList[3].t = { 0, 1 };

	m_pVertexList[4].p = Math::ScreenToNDC({ rect.right, rect.top });
	m_pVertexList[4].t = { 1, 0 };

	m_pVertexList[5].p = Math::ScreenToNDC({ rect.right, rect.bottom });
	m_pVertexList[5].t = { 1, 1 };

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pTextureFileName.data(), NULL, NULL, &m_pSRV, NULL);

	if (FAILED(hr)) {
		// TODO :: 로딩실패시.........
	}
	// 로딩성공시 샘플러스테이트 생성
	else {
		_CreateSamplerState();
	}

	Init();

	return true;
};

bool Mesh::Init()
{
	HRESULT hr;

	// 버퍼 정보를 채운다.
	D3D11_BUFFER_DESC bd;

	bd.ByteWidth = sizeof(decltype(m_pVertexList)::value_type) * m_pVertexList.size();
	// 그래픽카드 메모리를 사용
	bd.Usage = D3D11_USAGE_DEFAULT;
	// 버텍스 버퍼에 바인딩
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = m_pVertexList.data();
	// 그래픽카드 메모리에 버퍼를 생성한다
	// bd에 정보가 담겨있고 sd에 해당 버퍼메모리에 채워질 정점 정보가 담겨있다
	// 출력 매개변수 m_pVertexBuffer 로 정점들을 컨트롤 한ㄷ ㅏ . 
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	DWORD dwShaderFlags = 0;

	// 컴파일 오브젝트 파일로부터 버텍스쉐이더를 생성
	hr = m_pd3dDevice->CreateVertexShader(
		Shader::g_VS,
		sizeof(Shader::g_VS),
		nullptr,
		&m_pVS);

	hr = m_pd3dDevice->CreatePixelShader(
		Shader::g_PS,
		sizeof(Shader::g_PS),
		nullptr,
		&m_pPS);

	std::vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
		D3D11_INPUT_PER_VERTEX_DATA,0},

		{"COLOR",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,
		PCT_VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		PCT_VERTEX::POSITION + PCT_VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	if (layout.empty() == true) {
		// TODO :: layout  이 아직 준비되지 않았다 !!
	};

	hr = m_pd3dDevice->CreateInputLayout(
		layout.data(),
		layout.size(),
		Shader::g_VS,
		sizeof(Shader::g_VS),
		&m_pVertexLayout);

	UINT stride = sizeof(PCT_VERTEX);
	UINT offset = 0;
	
	if (m_pSRV) {
		m_pContext->PSSetShaderResources(0, 1, &m_pSRV);
	}
	if (m_pSamplerState) {
		m_pContext->PSSetSamplers(0, 1, &m_pSamplerState);
	}

	m_pContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pContext->IASetInputLayout(m_pVertexLayout);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVS, NULL, 0);
	m_pContext->HSSetShader(NULL, NULL, 0);
	m_pContext->DSSetShader(NULL, NULL, 0);
	m_pContext->GSSetShader(NULL, NULL, 0);
	m_pContext->PSSetShader(m_pPS, NULL, 0);

	return true; 
};
bool Mesh::Frame(float DeltaTime)
{
	return true;
};

bool Mesh::Render(float DeltaTime)
{
	OwnerPositionTORenderRECT();

	m_pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, m_pVertexList.data(), 0, 0);
	m_pContext->Draw(m_pVertexList.size(), 0);
	return true;
}

void Mesh::OwnerPositionTORenderRECT()& {
	if (IsValid(Owner) == false) {
		return;
	}

	RenderRect.left = Owner->Position.x;
	RenderRect.top = Owner->Position.y;
	RenderRect.right = RenderRect.right + Owner->Position.x;
	RenderRect.bottom = RenderRect.bottom + Owner->Position.y;

	FVector3 left_top = Math::ScreenToNDC({ RenderRect.left, RenderRect.top });
	FVector3 right_top = Math::ScreenToNDC({ RenderRect.right, RenderRect.top });
	FVector3 left_bottom = Math::ScreenToNDC({ RenderRect.left, RenderRect.bottom });
	FVector3 right_bottom = Math::ScreenToNDC({ RenderRect.right, RenderRect.bottom });

	m_pVertexList[0].p = left_top;
	m_pVertexList[1].p = right_top;
	m_pVertexList[2].p = left_bottom;
	m_pVertexList[3].p = left_bottom;
	m_pVertexList[4].p = right_top;
	m_pVertexList[5].p = right_bottom;
}

bool Mesh::Release() {

	DX_CheckValidRelease
	(m_pSamplerState,
	m_pSRV, 
	m_pVertexBuffer, 
	m_pVertexLayout, 
	m_pVS,
	m_pPS);

	return true;
};

bool Mesh::_CreateSamplerState()&
{
	D3D11_SAMPLER_DESC pSamplerDesc;
	ZeroMemory(&pSamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	pSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	pSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	pSamplerDesc.MinLOD = 0;
	pSamplerDesc.MaxLOD = 0;
	auto& [R, G, B, A] = pSamplerDesc.BorderColor;
	R = 0.f;
	G = 0.f;
	B = 1.f;
	A = 1.f;

	if (HRESULT hr;  m_pd3dDevice != nullptr) {
		hr	 = m_pd3dDevice->CreateSamplerState(&pSamplerDesc, &m_pSamplerState);

		if (FAILED(hr)) {
			return false;
		}
		else {
			return true;
		}
	}
	//pSamplerDesc.ComparsionFunc=
	//pSamplerDesc.MipLODBias= 
	//이방성 필터링pSamplerDesc.MaxAnisotropy = 16;
}
