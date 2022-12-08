#pragma once
#include <d3d11.h>
#include <map>
#include "BNS_EnumHandler.h"

class BNS_InputLayoutManager
{
public:
	BNS_InputLayoutManager();
	~BNS_InputLayoutManager();

public:
	void ChangeInputLayout(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type);

private:
	void Create_Mesh_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type);
	void Create_Texture_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type);
	void Create_COLOR_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type);
	void Create_COLORLERP_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type);
};

