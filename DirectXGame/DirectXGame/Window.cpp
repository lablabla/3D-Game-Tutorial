
#include <iostream>

#include "Window.h"


Window::Window() :
	m_hwnd(),
	m_isRunning(false)
{

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE: // Event fired when window is created
	{
		auto window = (Window*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)window);
		window->setHWND(hwnd);
		window->onCreate();
		break;
	}
	
	case WM_DESTROY: // Event fired when window is destroyed
	{
		auto window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX); 
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;

	if (!::RegisterClassEx(&wc))
	{
		std::cerr << "Failed registering window" << std::endl;
		return false;
	}


	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, wc.lpszClassName, L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, this);

	if (!m_hwnd)
	{
		return false;
	}

	// Show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_isRunning = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;
	onUpdated();

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}


	Sleep(1);
	return true;
}

bool Window::isRunning()
{
	return m_isRunning;
}

bool Window::release()
{
	if (::DestroyWindow(m_hwnd))
	{
		return false;
	}
	return true;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	m_hwnd = hwnd;
}

void Window::onDestroy()
{
	m_isRunning = false;
}

Window::~Window()
{

}
