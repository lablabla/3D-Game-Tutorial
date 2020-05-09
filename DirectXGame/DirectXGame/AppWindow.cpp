
#include "AppWindow.h"

#include "GraphicsEngine.h"

#include "SwapChain.h"

#include "DeviceContext.h"

AppWindow::AppWindow()
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
	if (m_swapChain)
	{
		RECT rc = getClientWindowRect();
		m_swapChain->init(m_hwnd, rc.right-rc.left, rc.bottom-rc.top);
	}
}

void AppWindow::onUpdated()
{
	auto ge = GraphicsEngine::get();
	auto immContext = ge->getImmediateDeviceContext();
	immContext->clearRenderTargetColor(m_swapChain, 1, 0, 0, 1);

	m_swapChain->present(false);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::get()->release();
	m_swapChain->release();
}
