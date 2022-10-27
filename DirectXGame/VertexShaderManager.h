#pragma once
#include <map>
#include "EnumHandler.h"
#include "Prerequisites.h"
#include "StructHandler.h"

class VertexShaderManager
{
public:
	VertexShaderManager();
	~VertexShaderManager();

public:
	void ChangeVertexShader(VertexShaderPtr& m_vs, VertexShaderType vs_type = VertexShaderType::DEFAULT);
	ShaderByteData GetVertexShaderData(VertexShaderType vs_type);

private:
	void CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, VertexShaderType vs_type);

private:
	std::map<VertexShaderType, ShaderByteData> VertexShaderMap;
};

