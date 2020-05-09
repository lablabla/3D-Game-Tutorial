
#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
	m_deviceContext(deviceContext)
{
}

DeviceContext::~DeviceContext()
{
}

bool DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r, g, b, a };
	m_deviceContext->ClearRenderTargetView(swapChain->m_rtd, clearColor);
	return true;
}

bool DeviceContext::release()
{
	if (m_deviceContext)
	{
		m_deviceContext->Release();
	}
	return true;
}
