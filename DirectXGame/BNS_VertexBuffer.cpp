#include "BNS_VertexBuffer.h"
#include "BNS_RenderSystem.h"
#include <exception>

#include "BNS_RenderBufferEngine.h"


BNS_VertexBuffer::BNS_VertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, BNS_InputLayoutType il_type,
                                   BNS_RenderSystem* system) : m_system(system), m_layout(0), m_buffer(0)
{
	// describe a buffer resource
	D3D11_BUFFER_DESC buff_desc = {};
	// checks if our buffer is accessible by CPU and GPU; default means it could be written by both CPU and GPU
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = size_vertex * size_list;
	// we want our buffer to be bind as a BNS_vertex_tex buffer
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	// passing the list of references of the vertices to the 'pSysMemory'
	init_data.pSysMem = list_vertices;

	m_size_vertex = size_vertex;
	m_size_list = size_list;

	if (FAILED(m_system->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		throw std::exception("BNS_VertexBuffer not created successfully");
	}

	BNS_RenderBufferEngine::get()->getInputLayoutManager()->ChangeInputLayout(&m_layout, il_type);
}

UINT BNS_VertexBuffer::getSizeVertexList()
{
	return this->m_size_list;
}

BNS_VertexBuffer::~BNS_VertexBuffer()
{
	m_layout->Release();
	m_buffer->Release();
}
