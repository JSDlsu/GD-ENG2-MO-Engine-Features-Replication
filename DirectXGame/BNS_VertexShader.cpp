#include "BNS_VertexShader.h"
#include "BNS_RenderSystem.h"
#include <exception>


BNS_VertexShader::BNS_VertexShader(const void* shader_byte_code, size_t byte_code_size, BNS_RenderSystem* system) : m_system(system)
{
	// creates a BNS_vertex_tex shader object from the DirectX3D Device
	if (!SUCCEEDED(m_system->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs)))
		throw std::exception("BNS_VertexShader not created successfully");
}

BNS_VertexShader::~BNS_VertexShader()
{
	m_vs->Release();
}