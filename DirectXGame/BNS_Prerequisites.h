#pragma once
#include <memory>

class BNS_SwapChain;
class BNS_DeviceContext;
class BNS_VertexBuffer;
class BNS_IndexBuffer;
class BNS_ConstantBuffer;
class BNS_VertexShader;
class BNS_PixelShader;
class BNS_RenderSystem;
class BNS_GraphicsEngine;
class BNS_Resource;
class BNS_ResourceManager;
class BNS_Texture;
class BNS_TextureManager;
class BNS_Mesh;
class BNS_MeshManager;
class BNS_Blender;
class BNS_GameObjectManager;
class BNS_Cube;
class BNS_PrimitiveCreation;
class BNS_Camera;
class BNS_VertexShaderManager;
class BNS_PixelShaderManager;
class BNS_InputLayoutManager;
class BNS_AppWindow;
class BNS_RenderToTexture;

typedef std::shared_ptr<BNS_SwapChain> SwapChainPtr;
typedef std::shared_ptr<BNS_DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<BNS_VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<BNS_IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<BNS_ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<BNS_VertexShader> VertexShaderPtr;
typedef std::shared_ptr<BNS_PixelShader> PixelShaderPtr;
typedef std::shared_ptr<BNS_Resource> ResourcePtr;
typedef std::shared_ptr<BNS_Texture> TexturePtr;
typedef std::shared_ptr<BNS_Mesh> MeshPtr;
typedef std::shared_ptr<BNS_RenderToTexture> RenderToTexturePtr;
typedef std::shared_ptr<BNS_Blender> BlenderPtr;