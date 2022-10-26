#include "VertexShaderManager.h"

#include "GraphicsEngine.h"

VertexShaderManager::VertexShaderManager(RenderSystem* m_render_system)
{
	// gets the byte code and size of the vertex_tex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	// access the VertexShader.hlsl and compile
	m_render_system->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(primitive and shader byte codes)
	::memcpy(base.m_byte_code, shader_byte_code, size_shader);
	// set the primitive size
	base.m_size = size_shader;
	m_render_system->releaseCompiledShader();
	// access the VertexMeshLayoutShader.hlsl and compile
	m_render_system->compileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(layout and shader byte codes)
	::memcpy(mesh.m_byte_code, shader_byte_code, size_shader);
	// set the layout size
	mesh.m_size = size_shader;
	m_render_system->releaseCompiledShader();
}

VertexShaderManager::~VertexShaderManager()
{
}

void VertexShaderManager::Get_VS_Default(void** byte_code, size_t* size)
{
	*byte_code = base.m_byte_code;
	*size = base.m_size;
}

void VertexShaderManager::Get_VS_Mesh(void** byte_code, size_t* size)
{
	*byte_code = mesh.m_byte_code;
	*size = mesh.m_size;
}
