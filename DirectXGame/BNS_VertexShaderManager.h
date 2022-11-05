#pragma once
#include <map>
#include "BNS_EnumHandler.h"
#include "BNS_Prerequisites.h"
#include "BNS_StructHandler.h"

class BNS_VertexShaderManager
{
public:
	BNS_VertexShaderManager();
	~BNS_VertexShaderManager();

public:
	void ChangeVertexShader(VertexShaderPtr& m_vs, BNS_VertexShaderType vs_type = BNS_VertexShaderType::TEXTURE);
	BNS_ShaderByteData GetVertexShaderData(BNS_VertexShaderType vs_type);

private:
	void CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, BNS_VertexShaderType vs_type);

private:
	std::map<BNS_VertexShaderType, BNS_ShaderByteData> VertexShaderMap;
};

