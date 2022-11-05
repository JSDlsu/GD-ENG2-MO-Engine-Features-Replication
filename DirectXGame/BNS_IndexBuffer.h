
#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

/*
 * Because indices need to be accessed by the GPU, they
 * need to be placed in a special resource structure: an
 * index buffer. Creating an index buffer is very similar
 * to creating a BNS_vertex_tex buffer, except that the index buffer
 * stores indices instead of vertices.*/
class BNS_IndexBuffer
{
public:
	BNS_IndexBuffer(void* list_indices, UINT size_list, BNS_RenderSystem* system);
	UINT getSizeIndexList();
	~BNS_IndexBuffer();
private:
	UINT m_size_list;
private:
	ID3D11Buffer* m_buffer;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_DeviceContext;
};