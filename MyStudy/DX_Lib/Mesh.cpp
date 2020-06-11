#include "Mesh.h"

bool Mesh::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,
	const std::wstring_view pTextureFileName,
	P3VERTEX* vertices,
	UINT iNumCount) {

	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
	m_pVertexList = vertices;	
	m_iNumVertex = iNumCount;
	// ȣ����� �ݵ�� ���Ѿ��� Create->Init;

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pTextureFileName.data(), NULL, NULL, &m_pSRV, NULL);

	if (FAILED(hr)) {
		// TODO :: �ε����н�.........
	}
	// �ε������� ���÷�������Ʈ ����
	else {
		_CreateSamplerState();
	}

	Init();

	return true;
};

bool Mesh::Init()
{
	HRESULT hr;

	// ���� ������ ä���.
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(P3VERTEX) * m_iNumVertex;
	// �׷���ī�� �޸𸮸� ���
	bd.Usage = D3D11_USAGE_DEFAULT;
	// ���ؽ� ���ۿ� ���ε�
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = m_pVertexList;
	// �׷���ī�� �޸𸮿� ���۸� �����Ѵ�
	// bd�� ������ ����ְ� sd�� �ش� ���۸޸𸮿� ä���� ���� ������ ����ִ�
	// ��� �Ű����� m_pVertexBuffer �� �������� ��Ʈ�� �Ѥ� �� . 
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	DWORD dwShaderFlags = 0;

	// ������ ������Ʈ ���Ϸκ��� ���ؽ����̴��� ����
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
		P3VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		P3VERTEX::POSITION + P3VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
	};

	if (layout.empty() == true) {
		// TODO :: layout  �� ���� �غ���� �ʾҴ� !!
	};

	hr = m_pd3dDevice->CreateInputLayout(
		layout.data(),
		layout.size(),
		Shader::g_VS,
		sizeof(Shader::g_VS),
		&m_pVertexLayout);

	UINT stride = sizeof(P3VERTEX);
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
bool Mesh::Frame()
{
	return true;
};

bool Mesh::Render()
{
	m_pContext->Draw(m_iNumVertex, 0);
	return true;
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
	//�̹漺 ���͸�pSamplerDesc.MaxAnisotropy = 16;
}
