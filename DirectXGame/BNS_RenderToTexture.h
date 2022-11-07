#pragma oncE
#include <d3d11.h>

class BNS_RenderToTexture
{
public:
	BNS_RenderToTexture(int textureWidth, int textureHeight);
	BNS_RenderToTexture(const BNS_RenderToTexture&);
	~BNS_RenderToTexture();
	
	void Shutdown();

	void SetRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*);
	void ClearRenderTarget(ID3D11DeviceContext*, ID3D11DepthStencilView*, float, float, float, float);
	ID3D11ShaderResourceView* GetShaderResourceView();

private:
	ID3D11Texture2D* m_renderTargetTexture;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11ShaderResourceView* m_shaderResourceView;
};