
#include "GraphicsEngine.h"
#include "SwapChain.h"

GraphicsEngine::GraphicsEngine() :
	m_d3dDevice(nullptr),
	m_featureLevel(D3D_FEATURE_LEVEL_11_0),
	m_immContext(nullptr),
	m_dxgiDevice(nullptr),
	m_dxgiAdapter(nullptr),
	m_dxgiFactory(nullptr)
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

GraphicsEngine* GraphicsEngine::get()
{
	static GraphicsEngine engine;
	return &engine;
}
