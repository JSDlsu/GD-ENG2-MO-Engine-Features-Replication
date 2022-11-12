#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

class BNS_RenderToTexture
{
public:
	BNS_RenderToTexture(int textureWidth, int textureHeight);
	BNS_RenderToTexture(const BNS_RenderToTexture&);
	~BNS_RenderToTexture();
	void resize(unsigned width, unsigned height);
	void reloadBuffers(unsigned width, unsigned height);

	ID3D11ShaderResourceView* GetShaderResourceView();

private:
	ID3D11Texture2D* m_rtt = nullptr;
	ID3D11RenderTargetView* m_rtv = nullptr;
	ID3D11ShaderResourceView* m_srv = nullptr;
private:
	friend class BNS_DeviceContext;
};