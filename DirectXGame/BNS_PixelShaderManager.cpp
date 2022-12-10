#include "BNS_PixelShaderManager.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_ShaderEngine.h"

BNS_PixelShaderManager::BNS_PixelShaderManager()
{
	CompilePixelShader(L"BNS_PixelTex.hlsl", "psmain", BNS_PixelShaderType::TEXTURE);
	CompilePixelShader(L"BNS_PixelMesh.hlsl", "psmain", BNS_PixelShaderType::MESH);
	CompilePixelShader(L"BNS_PixelColor.hlsl", "psmain", BNS_PixelShaderType::COLOR);
	CompilePixelShader(L"BNS_PixelColorLerp.hlsl", "psmain", BNS_PixelShaderType::COLOR_LERP);
	CompilePixelShader(L"BNS_PixelLight.hlsl", "psmain", BNS_PixelShaderType::LIGHTING);
	CompilePixelShader(L"BNS_PixelSkyBox.hlsl", "psmain", BNS_PixelShaderType::SKYBOX);
	CompilePixelShader(L"BNS_PixelEarth.hlsl", "psmain", BNS_PixelShaderType::EARTH);
	CompilePixelShader(L"BNS_PixelPointLight.hlsl", "psmain", BNS_PixelShaderType::POINT_LIGHT);
}

BNS_PixelShaderManager::~BNS_PixelShaderManager()
{
}

void BNS_PixelShaderManager::ChangePixelShader(PixelShaderPtr& m_vs, BNS_PixelShaderType ps_type)
{
	BNS_ShaderByteData l_vs = GetPixelShaderData(ps_type);

	// after a successful compiling, create the BNS_vertex_tex buffer then
	m_vs = BNS_GraphicsEngine::get()->getRenderSystem()->CreatePixelShader(l_vs.m_byte_code, l_vs.m_size);
}

BNS_ShaderByteData BNS_PixelShaderManager::GetPixelShaderData(BNS_PixelShaderType ps_type)
{
	// search the pixelShaderData in the map collection
	for (auto it = PixelShaderMap.begin(); it != PixelShaderMap.end(); ++it)
		if (it->first == ps_type)
			return it->second;

	BNS_ShaderByteData no_result;
	return no_result;
}

void BNS_PixelShaderManager::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name,
	BNS_PixelShaderType ps_type)
{
	BNS_ShaderByteData m_data;
	// gets the byte code and size of the BNS_vertex_tex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;

	// access the VertexMeshLayoutShader.hlsl and compile
	BNS_GraphicsEngine::get()->getRenderSystem()->CompilePixelShader(file_name, entry_point_name, &shader_byte_code, &size_shader);
	// copy the bytecode into our public field(layout and shader byte codes)
	::memcpy(m_data.m_byte_code, shader_byte_code, size_shader);
	// set the layout size
	m_data.m_size = size_shader;
	// release compiled shader
	BNS_GraphicsEngine::get()->getRenderSystem()->ReleaseCompiledShader();

	// add the byteData obj to the map
	PixelShaderMap.insert(std::pair<BNS_PixelShaderType, BNS_ShaderByteData>(ps_type, m_data));
}
