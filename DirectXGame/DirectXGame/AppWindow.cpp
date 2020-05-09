
#include "AppWindow.h"

#include "GraphicsEngine.h"

#include "SwapChain.h"

#include "DeviceContext.h"

#include "VertexBuffer.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};


AppWindow::AppWindow() :
	m_swapChain(nullptr),
	m_vb(nullptr)
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	auto ge = GraphicsEngine::get();
	ge->init();
	m_swapChain = ge->createSwapChain();
	if (!m_swapChain)
	{
		return;
	}
	RECT rc = getClientWindowRect();
	m_swapChain->init(m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	vertex list[] =
	{
		{-0.5f, -0.5f, 0.0f},
		{0.0f, 0.5f, 0.0f},
		{0.5f, -0.5f, 0.0f},
	};
	UINT listSize = ARRAYSIZE(list);

	void* shaderByteCode = nullptr;
	UINT shaderByteSize = 0;

	ge->createShaders();
	ge->getShaderBufferAndSize(&shaderByteCode, &shaderByteSize);

	m_vb = ge->createVertexBuffer();
	m_vb->load(list, sizeof(vertex), listSize, shaderByteCode, shaderByteSize);
}

void AppWindow::onUpdated()
{
	auto ge = GraphicsEngine::get();
	auto immContext = ge->getImmediateDeviceContext();
	immContext->clearRenderTargetColor(m_swapChain, 1, 0, 0, 1);

	auto rc = getClientWindowRect();
	auto immDeviceContext = ge->getImmediateDeviceContext();
	immDeviceContext->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);
	ge->setShaders();

	immDeviceContext->setVertexBuffer(m_vb);

	immDeviceContext->drawTriangleList(m_vb->getListVertexSize(), 0);
	m_swapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	m_vb->release();
	m_swapChain->release();
	GraphicsEngine::get()->release();
}
