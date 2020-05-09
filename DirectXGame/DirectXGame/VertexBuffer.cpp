#include "VertexBuffer.h"

#include "GraphicsEngine.h"

VertexBuffer::VertexBuffer() :
	m_vertexSize(0),
	m_listSize(0),
	m_buffer(nullptr),
	m_layout(nullptr)
{
}

VertexBuffer::~VertexBuffer()
{
}

bool VertexBuffer::load(void* list, UINT vertexSize, UINT listSize, void* shaderByteCode, UINT shaderByteSize)
{
	release(false);

	auto ge = GraphicsEngine::get();

	D3D11_BUFFER_DESC buffDesc{};
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.ByteWidth = vertexSize * listSize;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = list;
	m_vertexSize = vertexSize;
	m_listSize = listSize;

	auto result = ge->m_d3dDevice->CreateBuffer(&buffDesc, &initData, &m_buffer);
	if (FAILED(result))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION",	0,		DXGI_FORMAT_R32G32B32_FLOAT, 0,		0,			D3D11_INPUT_PER_VERTEX_DATA, 0}	
	};

	UINT layoutSize = ARRAYSIZE(layout);

	result = ge->m_d3dDevice->CreateInputLayout(layout, layoutSize, shaderByteCode, shaderByteSize, &m_layout);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

bool VertexBuffer::release(bool deleteInstance)
{
	if (m_buffer)
	{
		m_buffer->Release();
	}
	if (m_layout)
	{
		m_layout->Release();
	}
	if (deleteInstance)
	{
		delete this;
	}
	return false;
}

UINT VertexBuffer::getListVertexSize()
{
	return m_listSize;
}
