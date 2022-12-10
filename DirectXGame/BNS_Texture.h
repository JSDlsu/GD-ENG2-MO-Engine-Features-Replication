#pragma once
#include "BNS_Resource.h"
#include <d3d11.h>

/*
 *
 */
class BNS_Texture : public BNS_Resource
{
public:
	BNS_Texture(const wchar_t* full_path);
	~BNS_Texture();
public:
	ID3D11Resource* GetTexture();
	ID3D11ShaderResourceView* GetShaderResourceView();
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
	ID3D11SamplerState* m_sampler_state = nullptr;
private:
	friend class BNS_DeviceContext;
};