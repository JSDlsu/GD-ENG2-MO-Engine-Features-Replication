#pragma once
#include "Prerequisites.h"

struct vertexByteData
{
	void* m_byte_code[2048];
	size_t m_size;
};

class VertexShaderManager
{
public:
	VertexShaderManager(RenderSystem* m_render_system);
	~VertexShaderManager();

public:
	void Get_VS_Default(void** byte_code, size_t* size);
	void Get_VS_Mesh(void** byte_code, size_t* size);

private:
	vertexByteData base;
	vertexByteData mesh;
};

