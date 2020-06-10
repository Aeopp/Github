#include "Mesh.h"

bool Mesh::Create(
	ID3D11Device* pd3dDevice, 
	ID3D11DeviceContext* pContext,
	P3VERTEX* vertices, 
	UINT iNumCount){

	m_pd3dDevice = pd3dDevice;
	m_pContext = pContext;
	m_pVertexList = vertices;
	m_iNumVertex = iNumCount;

	Init();

	return true; 
}

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
	ID3DBlob* pVSBuf = nullptr;
	ID3DBlob* pErrorBuf = nullptr;

	// ������ �о�鿩�� ������ �õ�
	// ���ϸ� �����Լ����� ������ ���� 
	hr = D3DX11CompileFromFile(
		L"VS.hlsl", NULL, NULL,
		"VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, &pErrorBuf, NULL);

	// ������ ���н� ���� ���� ���
	if (FAILED(hr)) {
		OutputDebugStringA((char*)pErrorBuf->GetBufferPointer());
	}

	// ������ ������Ʈ ���Ϸκ��� ���ؽ����̴��� ����
	hr = m_pd3dDevice->CreateVertexShader(
		pVSBuf->GetBufferPointer(),
		pVSBuf->GetBufferSize(),
		NULL,
		&m_pVS);

	ID3DBlob* pPSBuf = nullptr;
	
	hr = D3DX11CompileFromFile(
		L"PS.hlsl",NULL,NULL,
		"PS",
		"ps_5_0",
		0, NULL, NULL,
		&pPSBuf, &pErrorBuf, NULL);

	if (FAILED(hr)) {
		OutputDebugStringA((char*)pErrorBuf->GetBufferPointer());
	};

	hr = m_pd3dDevice->CreatePixelShader(pPSBuf->GetBufferPointer(),
		pPSBuf->GetBufferSize(),
		NULL,
		&m_pPS);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,
		D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	hr = m_pd3dDevice->CreateInputLayout(
		layout,
		1,
		pVSBuf->GetBufferPointer(),
		pVSBuf->GetBufferSize(),
		&m_pVertexLayout);

	if (pVSBuf)pVSBuf->Release();
	if (pPSBuf)pPSBuf->Release();
	if (pErrorBuf)pErrorBuf->Release();

	UINT stride = sizeof(P3VERTEX);
	UINT offset = 0;
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
}

bool Mesh::Render()
{
	m_pContext->Draw(6, 0);
	return true;
}

bool Mesh::Release(){

	if (m_pVertexBuffer)m_pVertexBuffer->Release();
	if (m_pVertexLayout)m_pVertexLayout->Release();
	if (m_pVS)m_pVS->Release();
	if (m_pPS)m_pPS->Release();
	return true; 
}
