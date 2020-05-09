#pragma once

#include <d3d11.h>

class DeviceContext;
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	bool load(void* list, UINT vertexSize, UINT listSize, void* shaderByteCode, UINT shaderByteSize);
	bool release(bool deleteInstance = true);

	UINT getListVertexSize();

private:
	UINT m_vertexSize;
	UINT m_listSize;

	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;


private:
	friend class DeviceContext;
};

