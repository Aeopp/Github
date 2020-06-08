#pragma once
#include "Std.h"
class Device
{
public :
	ID3D11Device* m_pd3dDevice;
	ID3D11DeviceContext* m_pContext;
	IDXGISwapChain* m_pSwapChain;
	ID3D11RenderTargetView* m_pRTV;
	IDXGIFactory* m_pGIFactory;
	D3D11_VIEWPORT m_vp;
public :
	bool SetD3DDevice(UINT width, UINT height);
	bool CreateGIFactory();
	bool CreateDevice();
	bool CreateSwapChain(UINT width, UINT height);
	bool CreateRenderTarget();
	bool CreateViewport();
	bool ReleaseDevice();
	virtual void ResizeDevice(UINT width, UINT height);
	virtual void CreateDXResource();
	virtual void DeleteDXResource();
public :
	Device();
	virtual ~Device(); 
};

