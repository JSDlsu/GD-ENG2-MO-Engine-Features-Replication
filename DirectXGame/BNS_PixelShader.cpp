#include "BNS_PixelShader.h"
#include "BNS_RenderSystem.h"
#include <exception>


BNS_PixelShader::BNS_PixelShader(const void* shader_byte_code, size_t byte_code_size, BNS_RenderSystem* system) : m_system(system)
{
	if (!SUCCEEDED(m_system->m_d3d_device->CreatePixelShader(shader_byte_code, byte_code_size, nullptr, &m_ps)))
		throw std::exception("BNS_PixelShader not created successfully");
	
}

BNS_PixelShader::~BNS_PixelShader()
{
	m_ps->Release();
}