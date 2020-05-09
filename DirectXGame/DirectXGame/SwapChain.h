#pragma once

#include <d3d11.h>

class SwapChain
{
public:
	SwapChain();
	~SwapChain();

	// Initializes the swap chain
	bool init(HWND hwnd, UINT width, UINT height);

	// Release resources of the swap chain
	bool release();

private:
	IDXGISwapChain* m_swapChain;
};

