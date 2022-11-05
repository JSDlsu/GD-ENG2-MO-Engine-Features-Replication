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
private:
	ID3D11Resource* m_texture = nullptr;
	ID3D11ShaderResourceView* m_shader_res_view = nullptr;
private:
	friend class DeviceContext;
};