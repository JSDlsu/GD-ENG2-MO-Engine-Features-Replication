#include "InputLayoutManager.h"

#include "BNS_EnumHandler.h"
#include "BNS_GraphicsEngine.h"
#include "ShaderEngine.h"

InputLayoutManager::InputLayoutManager()
{
}

InputLayoutManager::~InputLayoutManager()
{

}

void InputLayoutManager::ChangeInputLayout(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type)
{
	switch(il_type)
	{
	case BNS_InputLayoutType::MESH:
	case BNS_InputLayoutType::TEXTURE:
	{
		Create_Texture_IL(m_layout, BNS_InputLayoutType::TEXTURE, BNS_VertexShaderType::TEXTURE);
	}break;
	case BNS_InputLayoutType::COLOR:
	{
		Create_COLOR_IL(m_layout, BNS_InputLayoutType::COLOR, BNS_VertexShaderType::COLOR);
	}break;
	case BNS_InputLayoutType::COLOR_LERP:
	{
		Create_COLORLERP_IL(m_layout, BNS_InputLayoutType::COLOR_LERP, BNS_VertexShaderType::COLOR_LERP);
	}break;
	}
}

void InputLayoutManager::Create_Texture_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type)
{
	// defines the attribute of our BNS_vertex_tex buffer type
	// contains all the information about the attributes that will compose our BNS_vertex_tex type
	// the layout for our BNS_vertex_tex list[] in BNS_AppWindow
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	BNS_ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);
	
	if (FAILED(BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}
}

void InputLayoutManager::Create_COLOR_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 },
	};

	UINT size_layout = ARRAYSIZE(layout);

	BNS_ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);

	if (FAILED(BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}
}

void InputLayoutManager::Create_COLORLERP_IL(ID3D11InputLayout** m_layout, BNS_InputLayoutType il_type, BNS_VertexShaderType vs_type)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 },
		{ "COLOR", 1,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	BNS_ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);

	if (FAILED(BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}
	
}
