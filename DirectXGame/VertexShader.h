#pragma once
#include <d3d11.h>
#include "Prerequisites.h"

/*
 *A vertex_tex shader is a program written in HLSL, executed on the GPU, which
 *inputs a vertex_tex and outputs a vertex_tex. Every drawn vertex_tex goes through the
 *vertex_tex shader. This enables the programmer to do specialized work on a per
 *vertex_tex basis to achieve various rendering effects. The values output from
 *the vertex_tex shader are passed on to the next stage in the pipeline.
 */
class VertexShader
{
public:
	VertexShader(const void* shader_byte_code, size_t byte_code_size, RenderSystem* system);
	~VertexShader();
private:
	ID3D11VertexShader* m_vs;
	RenderSystem* m_system = nullptr;
private:
	friend class RenderSystem;
	friend class DeviceContext;
};