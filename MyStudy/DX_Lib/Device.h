#pragma once
#include "Std.h"
#include <functional>
class Device  : public SingleTon<Device>
{
public :
	ID3D11Device* m_pd3dDevice = nullptr;
	ID3D11DeviceContext* m_pContext = nullptr;
	IDXGISwapChain* m_pSwapChain = nullptr;
	ID3D11RenderTargetView* m_pRTV = nullptr;
	IDXGIFactory* m_pGIFactory= nullptr;
	D3D11_VIEWPORT m_vp;
public:
	inline ID3D11Device* GetDevice() const& {
		return m_pd3dDevice;
	};
	inline ID3D11DeviceContext* GetContext()const& {
		return m_pContext;
	}
public :
	bool SetD3DDevice(UINT width, UINT height);
	bool CreateGIFactory();
	bool CreateDevice();
	bool CreateSwapChain(UINT width, UINT height);
	bool CreateRenderTarget();
	bool CreateViewport();
	bool ReleaseDevice();
	std::function<void()> CreateDXResource{};
	std::function<void()> DeleteDXResource{};
	std::function<void(UINT, UINT)> ResizeDevice{};
	//virtual void ResizeDevice(UINT width, UINT height);
public :

	DECLARE_SINGLETON(Device);
};

