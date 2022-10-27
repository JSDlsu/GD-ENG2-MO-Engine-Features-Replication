#include "VertexShaderManager.h"

#include <iostream>

#include "GraphicsEngine.h"

VertexShaderManager::VertexShaderManager()
{
	CompileVertexShaders(L"VertexShader.hlsl", "vsmain", base);
	CompileVertexShaders(L"VertexMeshLayoutShader.hlsl", "vsmain", mesh);
	std::cout << "Compile shader" << std::endl;
}

VertexShaderManager::~VertexShaderManager()
{
}

VertexByteData VertexShaderManager::Get_VS_Default()
{
	return base;
}

VertexByteData VertexShaderManager::Get_VS_Mesh()
{
	return mesh;
}

void VertexShaderManager::CompileVertexShaders(const wchar_t* file_name, const char* entry_point_name,
	VertexByteData& m_data)
{
	// gets the byte code and size of the vertex_tex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// access the VertexMeshLayoutShader.hlsl and compile
	GraphicsEngine::get()->getRenderSystem()->compileVertexShader(file_name, entry_point_name, &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(layout and shader byte codes)
	::memcpy(m_data.m_byte_code, shader_byte_code, size_shader);
	// set the layout size
	m_data.m_size = size_shader;
	// release compiled shader
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	m_data.m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);
	
}
