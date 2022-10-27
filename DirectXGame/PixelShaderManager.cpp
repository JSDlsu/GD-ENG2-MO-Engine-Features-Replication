#include "PixelShaderManager.h"
#include "GraphicsEngine.h"
#include "ShaderEngine.h"

PixelShaderManager::PixelShaderManager()
{
	CompilePixelShader(L"PixelShader.hlsl", "psmain", PixelShaderType::DEFAULT);
}

PixelShaderManager::~PixelShaderManager()
{
}

void PixelShaderManager::ChangePixelShader(PixelShaderPtr& m_vs, PixelShaderType ps_type)
{
	ShaderByteData l_vs = GetPixelShaderData(ps_type);

	// after a successful compiling, create the vertex_tex buffer then
	m_vs = GraphicsEngine::get()->getRenderSystem()->createPixelShader(l_vs.m_byte_code, l_vs.m_size);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();
}

ShaderByteData PixelShaderManager::GetPixelShaderData(PixelShaderType ps_type)
{
	for (auto it = PixelShaderMap.begin(); it != PixelShaderMap.end(); ++it)
		if (it->first == ps_type)
			return it->second;

	ShaderByteData no_result;
	return no_result;
}

void PixelShaderManager::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name,
	PixelShaderType ps_type)
{
	ShaderByteData m_data;
	// gets the byte code and size of the vertex_tex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// access the VertexMeshLayoutShader.hlsl and compile
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(file_name, entry_point_name, &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(layout and shader byte codes)
	::memcpy(m_data.m_byte_code, shader_byte_code, size_shader);
	// set the layout size
	m_data.m_size = size_shader;
	// release compiled shader
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// add the byteData obj to the map
	PixelShaderMap.insert(std::pair<PixelShaderType, ShaderByteData>(ps_type, m_data));
}
