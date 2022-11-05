#pragma once
#include <memory>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class IndexBuffer;
class ConstantBuffer;
class VertexShader;
class PixelShader;
class RenderSystem;
class BNS_GraphicsEngine;
class BNS_Resource;
class BNS_ResourceManager;
class BNS_Texture;
class BNS_TextureManager;
class BNS_Mesh;
class BNS_MeshManager;
class Blender;
class AGameObject;
class GameObjectManager;
class Cube;
class PrimitiveCreation;
class BNS_Camera;
class VertexShaderManager;
class PixelShaderManager;
class InputLayoutManager;
class BNS_AppWindow;

typedef std::shared_ptr<SwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<BNS_Resource> ResourcePtr;
typedef std::shared_ptr<BNS_Texture> TexturePtr;
typedef std::shared_ptr<BNS_Mesh> MeshPtr;
typedef std::shared_ptr<Blender> BlenderPtr;
typedef std::shared_ptr<AGameObject> AGameObjectPtr;
typedef std::shared_ptr<AGameObject> CameraPtr;