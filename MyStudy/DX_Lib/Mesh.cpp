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

	// 버퍼 정보를 채운다.
	D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof(P3VERTEX) * m_iNumVertex;
	// 그래픽카드 메모리를 사용
	bd.Usage = D3D11_USAGE_DEFAULT;
	// 버텍스 버퍼에 바인딩
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = m_pVertexList;
	// 그래픽카드 메모리에 버퍼를 생성한다
	// bd에 정보가 담겨있고 sd에 해당 버퍼메모리에 채워질 정점 정보가 담겨있다
	// 출력 매개변수 m_pVertexBuffer 로 정점들을 컨트롤 한ㄷ ㅏ . 
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	DWORD dwShaderFlags = 0;
	ID3DBlob* pVSBuf = nullptr;
	ID3DBlob* pErrorBuf = nullptr;

	// 파일을 읽어들여서 컴파일 시도
	// 파일명 파일함수네임 컴파일 버전 
	hr = D3DX11CompileFromFile(
		L"VS.hlsl", NULL, NULL,
		"VS", "vs_5_0", dwShaderFlags, NULL, NULL, &pVSBuf, &pErrorBuf, NULL);

	// 컴파일 실패시 실패 정보 출력
	if (FAILED(hr)) {
		OutputDebugStringA((char*)pErrorBuf->GetBufferPointer());
	}

	// 컴파일 오브젝트 파일로부터 버텍스쉐이더를 생성
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
