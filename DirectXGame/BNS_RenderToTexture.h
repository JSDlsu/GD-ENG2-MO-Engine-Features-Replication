#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

class BNS_RenderToTexture
{
public:
	BNS_RenderToTexture(int textureWidth, int textureHeight);
	BNS_RenderToTexture(const BNS_RenderToTexture&);
	~BNS_RenderToTexture();
	
	ID3D11ShaderResourceView* GetShaderResourceView();

private:
	ID3D11Texture2D* m_renderTargetTexture = nullptr;
	ID3D11RenderTargetView* m_renderTargetView = nullptr;
	ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
private:
	friend class BNS_DeviceContext;
};