#pragma once

#include <d3d11.h>

class DeviceContext;

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	// Initializes the swap chain
	bool init(HWND hwnd, UINT width, UINT height);

	bool present(bool vsync);

	// Release resources of the swap chain
	bool release();

private:
	IDXGISwapChain* m_swapChain;
	ID3D11RenderTargetView* m_rtd;

private:
	friend class DeviceContext;
};

