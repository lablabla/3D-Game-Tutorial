#pragma once

#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;

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
	VertexBuffer* createVertexBuffer();

	bool createShaders();
	bool setShaders();
	void getShaderBufferAndSize(void** bytecode, UINT* size);

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


	ID3DBlob* m_vsblob;
	ID3DBlob* m_psblob;
	ID3D11VertexShader* m_vs;
	ID3D11PixelShader* m_ps;

private:
	friend class SwapChain;
	friend class VertexBuffer;
};

