#pragma once
#include "EnumHandler.h"
#include "Prerequisites.h"
#include "VertexShaderManager.h"

class PixelShaderManager
{
public:
	PixelShaderManager();
	~PixelShaderManager();
public:
	void ChangePixelShader(PixelShaderPtr& m_vs, PixelShaderType ps_type = PixelShaderType::DEFAULT);
	ShaderByteData GetPixelShaderData(PixelShaderType ps_type);

private:
	void CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, PixelShaderType ps_type);

private:
	std::map<PixelShaderType, ShaderByteData> PixelShaderMap;
};

