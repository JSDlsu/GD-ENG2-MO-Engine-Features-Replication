#include "VertexShaderManager.h"
#include <iostream>
#include "GraphicsEngine.h"
#include "ShaderEngine.h"

VertexShaderManager::VertexShaderManager()
{
	CompileVertexShader(L"VertexShader.hlsl", "vsmain", VertexShaderType::DEFAULT);
	CompileVertexShader(L"VertexMeshLayoutShader.hlsl", "vsmain", VertexShaderType::MESH);
}

VertexShaderManager::~VertexShaderManager()
{
}

void VertexShaderManager::ChangeVertexShader(VertexShaderPtr& m_vs, VertexShaderType vs_type)
{
	ShaderByteData l_vs = GetVertexShaderData(vs_type);

	// after a successful compiling, create the vertex_tex buffer then
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(l_vs.m_byte_code, l_vs.m_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

ShaderByteData VertexShaderManager::GetVertexShaderData(VertexShaderType vs_type)
{
	for (auto it = VertexShaderMap.begin(); it != VertexShaderMap.end(); ++it)
		if (it->first == vs_type)
			return it->second;

	ShaderByteData no_result;
	return no_result;
}

void VertexShaderManager::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name,
                                              VertexShaderType vs_type)
{
	ShaderByteData m_data;
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

	// add the byteData obj to the map
	VertexShaderMap.insert(std::pair<VertexShaderType, ShaderByteData>(vs_type, m_data));
}
