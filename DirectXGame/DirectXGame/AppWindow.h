#pragma once

#include "Window.h"

class SwapChain;

class AppWindow : public Window
{
public:
	AppWindow();
	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdated() override;
	virtual void onDestroy() override;

private:
	SwapChain* m_swapChain;
};

