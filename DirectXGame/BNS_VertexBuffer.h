#pragma once
#include <d3d11.h>

#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"

// creates a list of data(vertexBuffer) on a specific attribute(inputLayout)
class BNS_VertexBuffer
{
public:
	BNS_VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, BNS_InputLayoutType il_type,
		BNS_RenderSystem* system);
	UINT getSizeVertexList();
	~BNS_VertexBuffer();
private:
	UINT m_size_vertex;
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	ID3D11InputLayout* m_layout;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_DeviceContext;
};