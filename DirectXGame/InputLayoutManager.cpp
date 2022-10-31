#include "InputLayoutManager.h"

#include "EnumHandler.h"
#include "GraphicsEngine.h"
#include "ShaderEngine.h"

InputLayoutManager::InputLayoutManager()
{
	Create_Texture_IL(InputLayoutType::TEXTURE, VertexShaderType::TEXTURE);
	Create_COLOR_IL(InputLayoutType::COLOR, VertexShaderType::COLOR);
	Create_COLORLERP_IL(InputLayoutType::COLOR_LERP, VertexShaderType::COLOR_LERP);
}

InputLayoutManager::~InputLayoutManager()
{
	for (auto it = VertexShaderMap.begin(); it != VertexShaderMap.end(); ++it)
	{
		it->second->Release();
	}
}

void InputLayoutManager::ChangeVertexShader(ID3D11InputLayout** m_layout, InputLayoutType il_type)
{
	for (auto it = VertexShaderMap.begin(); it != VertexShaderMap.end(); ++it)
		if (it->first == il_type)
			*m_layout = it->second;
}

void InputLayoutManager::Create_Texture_IL(InputLayoutType il_type, VertexShaderType vs_type)
{
	// defines the attribute of our vertex_tex buffer type
	// contains all the information about the attributes that will compose our vertex_tex type
	// the layout for our vertex_tex list[] in AppWindow
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{"TEXCOORD", 0,  DXGI_FORMAT_R32G32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);

	ID3D11InputLayout* m_layout = nullptr;

	if (FAILED(GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, &m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}

	// add the byteData obj to the map
	VertexShaderMap.insert(std::pair<InputLayoutType, ID3D11InputLayout*>(il_type, m_layout));
}

void InputLayoutManager::Create_COLOR_IL(InputLayoutType il_type, VertexShaderType vs_type)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 },
	};

	UINT size_layout = ARRAYSIZE(layout);

	ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);

	ID3D11InputLayout* m_layout = nullptr;

	if (FAILED(GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, &m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}

	// add the byteData obj to the map
	VertexShaderMap.insert(std::pair<InputLayoutType, ID3D11InputLayout*>(il_type, m_layout));
}

void InputLayoutManager::Create_COLORLERP_IL(InputLayoutType il_type, VertexShaderType vs_type)
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		//SEMANTIC NAME - SEMANTIC INDEX - FORMAT - INPUT SLOT - ALIGNED BYTE OFFSET - INPUT SLOT CLASS - INSTANCE DATA STEP RATE
		{"POSITION", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA ,0},
		{ "COLOR", 0,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,D3D11_INPUT_PER_VERTEX_DATA ,0 },
		{ "COLOR", 1,  DXGI_FORMAT_R32G32B32_FLOAT, 0, 24,D3D11_INPUT_PER_VERTEX_DATA ,0 }
	};

	UINT size_layout = ARRAYSIZE(layout);

	ShaderByteData l_vs = ShaderEngine::get()->getVertexShaderManager()->GetVertexShaderData(vs_type);

	ID3D11InputLayout* m_layout = nullptr;

	if (FAILED(GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateInputLayout(layout, size_layout, l_vs.m_byte_code, l_vs.m_size, &m_layout)))
	{
		throw std::exception("VertexBuffer not created successfully");
	}

	// add the byteData obj to the map
	VertexShaderMap.insert(std::pair<InputLayoutType, ID3D11InputLayout*>(il_type, m_layout));
}
