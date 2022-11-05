#pragma once
#include "BNS_RenderSystem.h"
#include "BNS_TextureManager.h"
#include "BNS_MeshManager.h"

// Singleton class
// initializes the BNS_RenderSystem
class BNS_GraphicsEngine
{
private:
	//Initialize the BNS_GraphicsEngine and DirectX 11 Device
	BNS_GraphicsEngine();
	//Release all the resources loaded
	~BNS_GraphicsEngine();
public:
	BNS_RenderSystem* getRenderSystem();
	BNS_TextureManager* getTextureManager();
	BNS_MeshManager* getMeshManager();
public:
	static BNS_GraphicsEngine* get();
	static void create();
	static void release();
private:
	BNS_RenderSystem* m_render_system = nullptr;
	BNS_TextureManager* m_tex_manager = nullptr;
	BNS_MeshManager* m_mesh_manager = nullptr;
	static BNS_GraphicsEngine* m_engine;
	
};

