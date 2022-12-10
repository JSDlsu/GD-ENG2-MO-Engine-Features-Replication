#include "BNS_VertexShaderManager.h"
#include <iostream>
#include "BNS_GraphicsEngine.h"
#include "BNS_ShaderEngine.h"

BNS_VertexShaderManager::BNS_VertexShaderManager()
{
	CompileVertexShader(L"BNS_VertexTex.hlsl", "vsmain", BNS_VertexShaderType::TEXTURE);
	CompileVertexShader(L"BNS_VertexMeshLayout.hlsl", "vsmain", BNS_VertexShaderType::MESH);
	CompileVertexShader(L"BNS_VertexColor.hlsl", "vsmain", BNS_VertexShaderType::COLOR);
	CompileVertexShader(L"BNS_VertexColorLerp.hlsl", "vsmain", BNS_VertexShaderType::COLOR_LERP);
	CompileVertexShader(L"BNS_VertexLight.hlsl", "vsmain", BNS_VertexShaderType::LIGHTING);
	CompileVertexShader(L"BNS_VertexPointLight.hlsl", "vsmain", BNS_VertexShaderType::POINT_LIGHT);
}

BNS_VertexShaderManager::~BNS_VertexShaderManager()
{
}

void BNS_VertexShaderManager::ChangeVertexShader(VertexShaderPtr& m_vs, BNS_VertexShaderType vs_type)
{
	BNS_ShaderByteData l_vs = GetVertexShaderData(vs_type);

	// after a successful compiling, create the BNS_vertex_tex buffer then
	m_vs = BNS_GraphicsEngine::get()->getRenderSystem()->CreateVertexShader(l_vs.m_byte_code, l_vs.m_size);
}

BNS_ShaderByteData BNS_VertexShaderManager::GetVertexShaderData(BNS_VertexShaderType vs_type)
{
	for (auto it = VertexShaderMap.begin(); it != VertexShaderMap.end(); ++it)
		if (it->first == vs_type)
			return it->second;

	BNS_ShaderByteData no_result;
	return no_result;
}

void BNS_VertexShaderManager::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name,
                                              BNS_VertexShaderType vs_type)
{
	BNS_ShaderByteData m_data;
	// gets the byte code and size of the BNS_vertex_tex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// access the VertexMeshLayoutShader.hlsl and compile
	BNS_GraphicsEngine::get()->getRenderSystem()->CompileVertexShader(file_name, entry_point_name, &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(layout and shader byte codes)
	::memcpy(m_data.m_byte_code, shader_byte_code, size_shader);
	// set the layout size
	m_data.m_size = size_shader;
	// release compiled shader
	BNS_GraphicsEngine::get()->getRenderSystem()->ReleaseCompiledShader();

	// add the byteData obj to the map
	VertexShaderMap.insert(std::pair<BNS_VertexShaderType, BNS_ShaderByteData>(vs_type, m_data));
}
