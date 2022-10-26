#pragma once
#include "RenderSystem.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "VertexShaderManager.h"
#include "PixelShaderManager.h"

// Singleton class
// initializes the RenderSystem
class GraphicsEngine
{
private:
	//Initialize the GraphicsEngine and DirectX 11 Device
	GraphicsEngine();
	//Release all the resources loaded
	~GraphicsEngine();
public:
	RenderSystem* getRenderSystem();
	TextureManager* getTextureManager();
	MeshManager* getMeshManager();
	VertexShaderManager* getVertexShaderManager();
	PixelShaderManager* getPixelShaderManager();
public:
	static GraphicsEngine* get();
	static void create();
	static void release();
private:
	RenderSystem* m_render_system = nullptr;
	TextureManager* m_tex_manager = nullptr;
	MeshManager* m_mesh_manager = nullptr;
	VertexShaderManager* m_vertexShader_manager = nullptr;
	PixelShaderManager* m_pixelShader_manager = nullptr;
	static GraphicsEngine* m_engine;
	
};

