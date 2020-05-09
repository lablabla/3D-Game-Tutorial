
#include "SwapChain.h"
#include "GraphicsEngine.h"

SwapChain::SwapChain() :
	m_swapChain(nullptr)
{
}

SwapChain::~SwapChain()
{
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
	auto graphicsEngine = GraphicsEngine::get();
	auto device = graphicsEngine->m_d3dDevice;
	
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;
	desc.BufferDesc.Width = width;
	desc.BufferDesc.Height = height;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = hwnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Windowed = TRUE;

	auto result = graphicsEngine->m_dxgiFactory->CreateSwapChain(device, &desc, &m_swapChain);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool SwapChain::release()
{
	if (m_swapChain)
	{
		m_swapChain->Release();
	}
	delete this;
	return true;
}
