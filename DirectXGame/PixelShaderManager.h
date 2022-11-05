#pragma once
#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"
#include "VertexShaderManager.h"

class PixelShaderManager
{
public:
	PixelShaderManager();
	~PixelShaderManager();
public:
	void ChangePixelShader(PixelShaderPtr& m_vs, BNS_PixelShaderType ps_type = BNS_PixelShaderType::TEXTURE);
	BNS_ShaderByteData GetPixelShaderData(BNS_PixelShaderType ps_type);

private:
	void CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, BNS_PixelShaderType ps_type);

private:
	std::map<BNS_PixelShaderType, BNS_ShaderByteData> PixelShaderMap;
};

