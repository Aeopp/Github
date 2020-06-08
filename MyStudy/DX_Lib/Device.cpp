#include "Device.h"

bool Device::CreateGIFactory()
{
    if (FAILED(CreateDXGIFactory(__uuidof(IDXGIFactory),
        (void**)&m_pGIFactory))) {
        return false; 
    }
     return true; 
}

bool Device::CreateDevice()
{
    UINT Flags = 0;
#ifdef _DEBUG
    Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG
    D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
    D3D_FEATURE_LEVEL FeatureLevel;
    D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;

    HRESULT hr = D3D11CreateDevice(
        NULL,
        DriverType,
        NULL,
        Flags,
        &pFeatureLevels,
        1,D3D11_SDK_VERSION,
        &m_pd3dDevice,
        &FeatureLevel,
        &m_pContext
    );
    if (FAILED(hr)) {
        return false;  
    }
    return true;
}

bool Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = g_rtClient.right;
    sd.BufferDesc.Height = g_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator= 1;
    sd.OutputWindow = g_hWnd;
    sd.Windowed = TRUE;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.SampleDesc.Count = 1;

    HRESULT hr = m_pGIFactory->CreateSwapChain(
        m_pd3dDevice, &sd, &m_pSwapChain);

    if (FAILED(hr)) {
        return false; 
    }
    return true;
}

bool Device::CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    HRESULT hr = m_pSwapChain->GetBuffer(0,
        __uuidof(ID3D11Texture2D),
        (void**)&pBackBuffer);

    if (FAILED(hr)) {
        return false;  
    }

    if (FAILED(m_pd3dDevice->CreateRenderTargetView(
        pBackBuffer,
        NULL,
        &m_pRTV))) {
        return false;  
    }
    pBackBuffer->Release();

    m_pContext->OMSetRenderTargets(1, &m_pRTV, NULL);

    return true;
}

bool Device::CreateViewport()
{
    return true;
}

bool Device::ReleaseDevice()
{
    if (m_pRTV)m_pRTV->Release();
    if (m_pSwapChain)m_pSwapChain->Release();
    if (m_pd3dDevice)m_pd3dDevice->Release();
    if (m_pContext)m_pContext->Release();
    if (m_pGIFactory)m_pGIFactory->Release();

    return true;
}

Device::Device()
{
    m_pGIFactory = nullptr;
    m_pd3dDevice = nullptr;
    m_pContext = nullptr;
    m_pSwapChain = nullptr;
    m_pRTV = nullptr;
}

Device::~Device()
{
}
