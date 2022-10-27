#pragma once
#include "Prerequisites.h"

struct VertexByteData
{
	void* m_byte_code[2048];
	size_t m_size;
	VertexShaderPtr m_vs;
};

class VertexShaderManager
{
public:
	VertexShaderManager();
	~VertexShaderManager();

public:
	VertexByteData Get_VS_Default();
	VertexByteData Get_VS_Mesh();

private:
	void CompileVertexShaders(const wchar_t* file_name, const char* entry_point_name, VertexByteData& m_data);

private:
	VertexByteData base;
	VertexByteData mesh;
};

