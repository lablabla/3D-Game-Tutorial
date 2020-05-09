#pragma once

#include <Windows.h>


class Window
{
public:
	Window();
	~Window();

	// Initializes the window
	bool init();

	bool broadcast();

	bool isRunning();

	// Releases the window
	bool release();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate() = 0;
	virtual void onUpdated() = 0;
	virtual void onDestroy();

protected:
	HWND m_hwnd;

	bool m_isRunning;
};

