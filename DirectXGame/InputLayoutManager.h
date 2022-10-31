#pragma once
#include <d3d11.h>
#include <map>
#include "EnumHandler.h"

class InputLayoutManager
{
public:
	InputLayoutManager();
	~InputLayoutManager();

public:
	void ChangeInputLayout(ID3D11InputLayout** m_layout, InputLayoutType il_type);

private:
	void Create_Texture_IL(ID3D11InputLayout** m_layout, InputLayoutType il_type, VertexShaderType vs_type);
	void Create_COLOR_IL(ID3D11InputLayout** m_layout, InputLayoutType il_type, VertexShaderType vs_type);
	void Create_COLORLERP_IL(ID3D11InputLayout** m_layout, InputLayoutType il_type, VertexShaderType vs_type);
};

