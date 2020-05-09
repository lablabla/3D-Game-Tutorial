
#include "AppWindow.h"

#include "GraphicsEngine.h"

#include "SwapChain.h"


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
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::get()->release();
	m_swapChain->release();
}
