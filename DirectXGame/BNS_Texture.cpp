#include "BNS_Texture.h"
#include <DirectXTex.h>
#include "BNS_GraphicsEngine.h"

BNS_Texture::BNS_Texture(const wchar_t* full_path) : BNS_Resource(full_path)
{
	// a scratchImage will contain the image's data
	DirectX::ScratchImage image_data;
	// can pass many types of images like PNG, JPG, and so on, and load them in memory
	HRESULT res = DirectX::LoadFromWICFile(full_path, DirectX::WIC_FLAGS_NONE, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		// creates the texture resource
		res = DirectX::CreateTexture(BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device, image_data.GetImages(),
			image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		if (FAILED(res)) throw std::exception("BNS_Texture not created successfully");
		// creates a description for the shaderResourceView
		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		D3D11_SAMPLER_DESC sample_desc = {};
		sample_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sample_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sample_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sample_desc.Filter = D3D11_FILTER_ANISOTROPIC;
		sample_desc.MinLOD = 0;
		sample_desc.MaxLOD = (UINT)image_data.GetMetadata().mipLevels;
			
		res = BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateSamplerState(&sample_desc, &m_sampler_state);
		if (FAILED(res)) throw std::exception("BNS_Texture not created successfully");

		// pass the description data to the shaderResourceView object
		res = BNS_GraphicsEngine::get()->getRenderSystem()->m_d3d_device->CreateShaderResourceView(m_texture, &desc,
			&m_shader_res_view);
		if (FAILED(res)) throw std::exception("BNS_Texture not created successfully");
	}
	else
	{
		throw std::exception("BNS_Texture not created successfully");
	}
}


BNS_Texture::~BNS_Texture()
{
	m_shader_res_view->Release();
	m_texture->Release();
}

ID3D11Resource* BNS_Texture::GetTexture()
{
	return m_texture;
}

ID3D11ShaderResourceView* BNS_Texture::GetShaderResourceView()
{
	return m_shader_res_view;
}
