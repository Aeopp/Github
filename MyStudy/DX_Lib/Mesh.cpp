#include "Mesh.h"
#include "Math.h"
#include "Actor.h"

bool Mesh::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,
	const std::wstring_view pTextureFileName,
<<<<<<< HEAD
	RECTANGLE rect,
	Actor* Owner) {
=======
	P3VERTEX* vertices,
	UINT iNumCount) {
>>>>>>> parent of 7fb459c... Revert "ÌÖçÏä§Ï≤ò Ïù¥ÎØ∏ÏßÄ ÎùÑÏö∞ÎäîÎç∞ÍπåÏßÄ Íµ¨ÌòÑ"

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
		// TODO :: ∑Œµ˘Ω«∆–Ω√.........
	}
	// ∑Œµ˘º∫∞¯Ω√ ª˘«√∑ØΩ∫≈◊¿Ã∆Æ ª˝º∫
	else {
		_CreateSamplerState();
	}

	HRESULT hr = D3DX11CreateShaderResourceViewFromFile(pd3dDevice, pTextureFileName.data(), NULL, NULL, &m_pSRV, NULL);

	if (FAILED(hr)) {
		// TODO :: ∑Œµ˘Ω«∆–Ω√.........
	}
	// ∑Œµ˘º∫∞¯Ω√ ª˘«√∑ØΩ∫≈◊¿Ã∆Æ ª˝º∫
	else {
		_CreateSamplerState();
	}

	Init();

	return true;
};

bool Mesh::Init()
{
	HRESULT hr;

	// πˆ∆€ ¡§∫∏∏¶ √§øÓ¥Ÿ.
	D3D11_BUFFER_DESC bd;

	bd.ByteWidth = sizeof(decltype(m_pVertexList)::value_type) * m_pVertexList.size();
	// ±◊∑°«»ƒ´µÂ ∏ﬁ∏∏Æ∏¶ ªÁøÎ
	bd.Usage = D3D11_USAGE_DEFAULT;
	// πˆ≈ÿΩ∫ πˆ∆€ø° πŸ¿Œµ˘
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	sd.pSysMem = m_pVertexList.data();
	// ±◊∑°«»ƒ´µÂ ∏ﬁ∏∏Æø° πˆ∆€∏¶ ª˝º∫«—¥Ÿ
	// bdø° ¡§∫∏∞° ¥„∞‹¿÷∞Ì sdø° «ÿ¥Á πˆ∆€∏ﬁ∏∏Æø° √§øˆ¡˙ ¡§¡° ¡§∫∏∞° ¥„∞‹¿÷¥Ÿ
	// √‚∑¬ ∏≈∞≥∫Øºˆ m_pVertexBuffer ∑Œ ¡§¡°µÈ¿ª ƒ¡∆Æ∑— «—§ß §ø . 
	hr = m_pd3dDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	DWORD dwShaderFlags = 0;

	// ƒƒ∆ƒ¿œ ø¿∫Í¡ß∆Æ ∆ƒ¿œ∑Œ∫Œ≈Õ πˆ≈ÿΩ∫Ω¶¿Ã¥ı∏¶ ª˝º∫
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
<<<<<<< HEAD
		PCT_VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		PCT_VERTEX::POSITION + PCT_VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
=======
		P3VERTEX::POSITION,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
		P3VERTEX::POSITION + P3VERTEX::COLOR,   D3D11_INPUT_PER_VERTEX_DATA,0}
>>>>>>> parent of 7fb459c... Revert "ÌÖçÏä§Ï≤ò Ïù¥ÎØ∏ÏßÄ ÎùÑÏö∞ÎäîÎç∞ÍπåÏßÄ Íµ¨ÌòÑ"
	};

	if (layout.empty() == true) {
		// TODO :: layout  ¿Ã æ∆¡˜ ¡ÿ∫Òµ«¡ˆ æ æ“¥Ÿ !!
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
<<<<<<< HEAD
=======

>>>>>>> parent of 7fb459c... Revert "ÌÖçÏä§Ï≤ò Ïù¥ÎØ∏ÏßÄ ÎùÑÏö∞ÎäîÎç∞ÍπåÏßÄ Íµ¨ÌòÑ"

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

<<<<<<< HEAD
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

=======
bool Mesh::Release() {

>>>>>>> parent of 7fb459c... Revert "ÌÖçÏä§Ï≤ò Ïù¥ÎØ∏ÏßÄ ÎùÑÏö∞ÎäîÎç∞ÍπåÏßÄ Íµ¨ÌòÑ"
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
	//¿ÃπÊº∫ « ≈Õ∏µpSamplerDesc.MaxAnisotropy = 16;
}
