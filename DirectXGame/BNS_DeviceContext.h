#pragma once
#include <d3d11.h>
#include "BNS_Prerequisites.h"

// Sets and generates the rendering commands to the selected driver
class BNS_DeviceContext
{
public:
	BNS_DeviceContext(ID3D11DeviceContext* device_context, BNS_RenderSystem* system);
	void clearRenderTargetColor(const SwapChainPtr& swap_chain, const RenderToTexturePtr& render_tex, float red,
	                            float green, float blue, float alpha);
	void clearRenderTargetColor(const SwapChainPtr& swap_chain, float red, float green, float blue, float alpha);
	void setVertexBuffer(const VertexBufferPtr& vertex_buffer);
	void setIndexBuffer(const IndexBufferPtr& index_buffer);

	void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
	void drawIndexedTriangleList(UINT index_count, UINT start_vertex_index, UINT start_index_location);
	void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);

	void setViewportSize(UINT width, UINT height);

	void setVertexShader(const VertexShaderPtr& vertex_shader);
	void setPixelShader(const PixelShaderPtr& pixel_shader);

	void setBlender(const BlenderPtr& blender);

	void setTexture(const VertexShaderPtr& vertex_shader, const TexturePtr* texture, unsigned int num_textures);
	void setTexture(const PixelShaderPtr& pixel_shader, const TexturePtr* texture, unsigned int num_textures);

	void setConstantBuffer(const VertexShaderPtr& vertex_shader, const ConstantBufferPtr& buffer);
	void setConstantBuffer(const PixelShaderPtr& pixel_shader, const ConstantBufferPtr& buffer);
	
	~BNS_DeviceContext();
private:
	ID3D11DeviceContext* m_device_context;
	BNS_RenderSystem* m_system = nullptr;
private:
	friend class BNS_ConstantBuffer;
};


