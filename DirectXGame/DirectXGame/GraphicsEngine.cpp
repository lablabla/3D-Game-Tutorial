
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"


#include <d3dcompiler.h>

GraphicsEngine::GraphicsEngine() :
	m_d3dDevice(nullptr),
	m_featureLevel(D3D_FEATURE_LEVEL_11_0),
	m_immContext(nullptr),
	m_dxgiDevice(nullptr),
	m_dxgiAdapter(nullptr),
	m_dxgiFactory(nullptr),
	m_immDeviceContext(nullptr),
	m_vsblob(nullptr),
	m_psblob(nullptr),
	m_vs(nullptr),
	m_ps(nullptr)
{
}

GraphicsEngine::~GraphicsEngine()
{
}

bool GraphicsEngine::init()
{
	D3D_DRIVER_TYPE driverType[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};

	D3D_FEATURE_LEVEL featureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT numOfFeatureLevel = ARRAYSIZE(featureLevel);

	HRESULT result = 0;
	for (const auto& type : driverType)
	{
		result = D3D11CreateDevice(NULL, type, NULL, NULL, featureLevel, numOfFeatureLevel, D3D11_SDK_VERSION,
			&m_d3dDevice, &m_featureLevel, &m_immContext);
		if (SUCCEEDED(result))
		{
			break;
		}
	}

	if (FAILED(result))
	{
		return false;
	}

	m_immDeviceContext = new DeviceContext(m_immContext);

	m_d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgiDevice));
	m_dxgiDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_dxgiAdapter));
	m_dxgiAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgiFactory));
	
	return true;
}

bool GraphicsEngine::release()
{
	if (m_dxgiDevice)
	{
		m_dxgiDevice->Release();
	}
	if (m_dxgiAdapter)
	{
		m_dxgiAdapter->Release();
	}
	if (m_dxgiFactory)
	{
		m_dxgiFactory->Release();
	}

	if (m_immDeviceContext)
	{
		m_immDeviceContext->release();
	}

	if (m_immContext)
	{
		m_immContext->Release();
	}

	if (m_d3dDevice)
	{
		m_d3dDevice->Release();
	}
	return true;
}

SwapChain* GraphicsEngine::createSwapChain()
{
	return new SwapChain();
}

DeviceContext* GraphicsEngine::getImmediateDeviceContext()
{
	return m_immDeviceContext;
}

VertexBuffer* GraphicsEngine::createVertexBuffer()
{
	return new VertexBuffer();
}

bool GraphicsEngine::createShaders()
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "main", "vs_5_0", NULL, NULL, &m_vsblob, &errblob);
	D3DCompileFromFile(L"shader.fx", nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &m_psblob, &errblob);
	m_d3dDevice->CreateVertexShader(m_vsblob->GetBufferPointer(), m_vsblob->GetBufferSize(), nullptr, &m_vs);
	m_d3dDevice->CreatePixelShader(m_psblob->GetBufferPointer(), m_psblob->GetBufferSize(), nullptr, &m_ps);
	return true;
}

bool GraphicsEngine::setShaders()
{
	m_immContext->VSSetShader(m_vs, nullptr, 0);
	m_immContext->PSSetShader(m_ps, nullptr, 0);
	return true;
}

void GraphicsEngine::getShaderBufferAndSize(void** bytecode, UINT* size)
{
	*bytecode = this->m_vsblob->GetBufferPointer();
	*size = (UINT)this->m_vsblob->GetBufferSize();
}

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}
