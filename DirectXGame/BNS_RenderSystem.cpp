#include "BNS_RenderSystem.h"
#include "BNS_SwapChain.h"
#include "BNS_DeviceContext.h"
#include "BNS_VertexBuffer.h"
#include "BNS_IndexBuffer.h"
#include "BNS_ConstantBuffer.h"
#include "BNS_VertexShader.h"
#include "BNS_PixelShader.h"

#include <d3dcompiler.h>
#include <exception>

#include "BNS_Blender.h"
#include "BNS_RenderToTexture.h"

BNS_RenderSystem::BNS_RenderSystem()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		// drawing calls are executed in the GPU which guarantees the (best performance); that's why it is first
		D3D_DRIVER_TYPE_HARDWARE,
		// the drawing calls are all executed in the CPU; (medium performance)
		D3D_DRIVER_TYPE_WARP,
		// (slowest performance)
		D3D_DRIVER_TYPE_REFERENCE
	};
	// get the size(unsigned int) of the array
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels,
			num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
		if (SUCCEEDED(res))
			break;
		++driver_type_index;
	}
	if (FAILED(res))
	{
		throw std::exception("BNS_RenderSystem not created successfully");
	}
	// instantiate the 'BNS_DeviceContext' class with the ID3D11DeviceContext* reference
	m_imm_device_context = std::make_shared<BNS_DeviceContext>(m_imm_context, this);

	/* IDXGI is the DirectX graphics infrastructure assistant that takes care of the low-level
	tasks that can be independent of the DirectX graphics runtime like the swap chain*/
	m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void**)&m_dxgi_device);
	m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), (void**)&m_dxgi_adapter);
	m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_dxgi_factory);

	InitRasterizerState();

}

BNS_RenderSystem::~BNS_RenderSystem()
{
	if (m_vsblob)m_vsblob->Release();
	if (m_psblob)m_psblob->Release();

	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();
	m_cull_back_state->Release();
	m_cull_front_state->Release();

	m_d3d_device->Release();
}

SwapChainPtr BNS_RenderSystem::CreateSwapChain(HWND hwnd, UINT width, UINT height)
{
	SwapChainPtr sc = nullptr;

	try
	{
		sc = std::make_shared<BNS_SwapChain>(hwnd, width, height, this);
	}
	catch(...){}
	return sc;
}


DeviceContextPtr BNS_RenderSystem::GetImmediateDeviceContext()
{
	return this->m_imm_device_context;
}

VertexBufferPtr BNS_RenderSystem::CreateVertexBuffer(void* list_vertices, UINT size_vertex, UINT size_list, BNS_InputLayoutType il_type)
{
	VertexBufferPtr vb = nullptr;
	try
	{
		vb = std::make_shared<BNS_VertexBuffer>(list_vertices, size_vertex, size_list, il_type, this);
	}
	catch (...) {}
	return vb;
}

IndexBufferPtr BNS_RenderSystem::CreateIndexBuffer(void* list_indices, UINT size_list)
{
	IndexBufferPtr ib = nullptr;
	try
	{
		ib = std::make_shared<BNS_IndexBuffer>(list_indices, size_list, this);
	}
	catch (...) {}
	return ib;
}

ConstantBufferPtr BNS_RenderSystem::CreateConstantBuffer(void* buffer, UINT size_buffer)
{
	ConstantBufferPtr cb = nullptr;
	try
	{
		cb = std::make_shared<BNS_ConstantBuffer>(buffer, size_buffer, this);
	}
	catch (...) {}
	return cb;
}

VertexShaderPtr BNS_RenderSystem::CreateVertexShader(const void* shader_byte_code, size_t byte_code_size)
{
	// a buffer that contains the error and warning messages in case the compilation fails
	VertexShaderPtr vs = nullptr;
	try
	{
		vs = std::make_shared<BNS_VertexShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return vs;
}

PixelShaderPtr BNS_RenderSystem::CreatePixelShader(const void* shader_byte_code, size_t byte_code_size)
{
	PixelShaderPtr ps = nullptr;
	try
	{
		ps = std::make_shared<BNS_PixelShader>(shader_byte_code, byte_code_size, this);
	}
	catch (...) {}
	return ps;
}

BlenderPtr BNS_RenderSystem::CreateBlender()
{
	BlenderPtr blender = nullptr;
	try
	{
		blender = std::make_shared<BNS_Blender>(this);
	}
	catch (...) {}
	return blender;
}

RenderToTexturePtr BNS_RenderSystem::CreateRenderToTexture(int textureWidth, int textureHeight)
{
	RenderToTexturePtr renderToTex = nullptr;
	try
	{
		renderToTex = std::make_shared<BNS_RenderToTexture>(textureWidth, textureHeight);
	}
	catch (...) {}
	return renderToTex;
}

bool BNS_RenderSystem::CompileVertexShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "vs_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

bool BNS_RenderSystem::CompilePixelShader(const wchar_t* file_name, const char* entry_point_name, void** shader_byte_code, size_t* byte_code_size)
{
	ID3DBlob* error_blob = nullptr;
	if (!SUCCEEDED(D3DCompileFromFile(file_name, nullptr, nullptr, entry_point_name, "ps_5_0", 0, 0, &m_blob, &error_blob)))
	{
		if (error_blob) error_blob->Release();
		return false;
	}

	*shader_byte_code = m_blob->GetBufferPointer();
	*byte_code_size = m_blob->GetBufferSize();

	return true;
}

void BNS_RenderSystem::ReleaseCompiledShader()
{
	if (m_blob)m_blob->Release();
}

void BNS_RenderSystem::SetRasterizerState(bool cull_front)
{
	if (cull_front)
		m_imm_context->RSSetState(m_cull_front_state);
	else
		m_imm_context->RSSetState(m_cull_back_state);

}

ID3D11Device* BNS_RenderSystem::GetDevice()
{
	return m_d3d_device;
}

ID3D11DeviceContext* BNS_RenderSystem::GetDeviceContext()
{
	return m_imm_context;
}

void BNS_RenderSystem::InitRasterizerState()
{
	// front state
	D3D11_RASTERIZER_DESC desc = {};
	desc.CullMode = D3D11_CULL_FRONT;
	desc.DepthClipEnable = true;
	desc.FillMode = D3D11_FILL_SOLID;
	m_d3d_device->CreateRasterizerState(&desc, &m_cull_front_state);
	// back state
	desc.CullMode = D3D11_CULL_BACK;
	m_d3d_device->CreateRasterizerState(&desc, &m_cull_back_state);
}
