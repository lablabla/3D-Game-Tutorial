#pragma once

#include <d3d11.h>

class SwapChain;
class VertexBuffer;

class DeviceContext
{
public:
    DeviceContext(ID3D11DeviceContext *deviceContext);
    ~DeviceContext();

    void clearRenderTargetColor(SwapChain* swapChain, float r, float g, float b, float a);
    void setVertexBuffer(VertexBuffer* vertexBuffer);
    void drawTriangleList(UINT numOfVertices, UINT startIndex);
    void setViewportSize(UINT width, UINT height);
    bool release();

private:
    ID3D11DeviceContext* m_deviceContext;

};

