
#include "DeviceContext.h"
#include "SwapChain.h"
#include "VertexBuffer.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext) :
	m_deviceContext(deviceContext)
{
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a)
{
	FLOAT clearColor[] = { r, g, b, a };
	m_deviceContext->ClearRenderTargetView(swapChain->m_rtd, clearColor);
	m_deviceContext->OMSetRenderTargets(1, &swapChain->m_rtd, NULL);
}

void DeviceContext::setVertexBuffer(VertexBuffer* vertexBuffer)
{
	UINT stride = vertexBuffer->m_vertexSize;
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer->m_buffer, &stride, &offset);

	m_deviceContext->IASetInputLayout(vertexBuffer->m_layout);
}

void DeviceContext::drawTriangleList(UINT numOfVertices, UINT startIndex)
{
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceContext->Draw(numOfVertices, startIndex);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp{};
	vp.Width = static_cast<float>(width);
	vp.Height = static_cast<float>(height);
	vp.MinDepth = 0;
	vp.MaxDepth = 1.0;
	m_deviceContext->RSSetViewports(1, &vp);
}

bool DeviceContext::release()
{
	if (m_deviceContext)
	{
		m_deviceContext->Release();
	}
	return true;
}
