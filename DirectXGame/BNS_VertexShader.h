#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

/*
 *A BNS_vertex_tex shader is a program written in HLSL, executed on the GPU, which
 *inputs a BNS_vertex_tex and outputs a BNS_vertex_tex. Every drawn BNS_vertex_tex goes through the
 *BNS_vertex_tex shader. This enables the programmer to do specialized work on a per
 *BNS_vertex_tex basis to achieve various rendering effects. The values output from
 *the BNS_vertex_tex shader are passed on to the next stage in the pipeline.
 */
class BNS_VertexShader
{
public:
	BNS_VertexShader(const void* shader_byte_code, size_t byte_code_size, BNS_RenderSystem* system);
	~BNS_VertexShader();
private:
	ID3D11VertexShader* m_vs;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_RenderSystem;
	friend class BNS_DeviceContext;
};