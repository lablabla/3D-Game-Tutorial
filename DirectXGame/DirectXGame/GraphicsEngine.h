#pragma once

#include <d3d11.h>

class SwapChain;
class DeviceContext;

class GraphicsEngine
{
public:
	~GraphicsEngine();

	// Initializes GraphicsEngine and DirectX 11
	bool init();
	
	// Release graphics engine related resources
	bool release();

public:
	SwapChain* createSwapChain();
	DeviceContext* getImmediateDeviceContext();
	static GraphicsEngine* get();

private:
	GraphicsEngine();

	ID3D11Device* m_d3dDevice;
	D3D_FEATURE_LEVEL m_featureLevel;
	ID3D11DeviceContext* m_immContext;

	IDXGIDevice* m_dxgiDevice;
	IDXGIAdapter* m_dxgiAdapter;
	IDXGIFactory* m_dxgiFactory;

	DeviceContext* m_immDeviceContext;

private:
	friend class SwapChain;

};

