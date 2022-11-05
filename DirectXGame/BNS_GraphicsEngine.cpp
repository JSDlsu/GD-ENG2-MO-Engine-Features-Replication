#include "BNS_GraphicsEngine.h"
#include "BNS_RenderSystem.h"
#include <exception>
#include <iostream>

BNS_GraphicsEngine* BNS_GraphicsEngine::m_engine = nullptr;

BNS_GraphicsEngine::BNS_GraphicsEngine()
{
	try
	{
		// instantiate our BNS_RenderSystem
		m_render_system = new BNS_RenderSystem();
	}
	catch (...)
	{
		throw std::exception("BNS_GraphicsEngine not created successfully");
	}
	try
	{
		// instantiate our BNS_TextureManager
		m_tex_manager = new BNS_TextureManager();
	}
	catch (...)
	{
		throw std::exception("BNS_TextureManager not created successfully");
	}
	try
	{
		// instantiate our BNS_TextureManager
		m_mesh_manager = new BNS_MeshManager();
	}
	catch (...)
	{
		throw std::exception("BNS_MeshManager not created successfully");
	}
}

BNS_GraphicsEngine::~BNS_GraphicsEngine()
{
	BNS_GraphicsEngine::m_engine = nullptr;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;
}

BNS_RenderSystem* BNS_GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

BNS_TextureManager* BNS_GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

BNS_MeshManager* BNS_GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

BNS_GraphicsEngine* BNS_GraphicsEngine::get()
{
	return m_engine;
}

void BNS_GraphicsEngine::create()
{
	if (BNS_GraphicsEngine::m_engine) 
		throw std::exception("BNS_GraphicsEngine already created");
	BNS_GraphicsEngine::m_engine = new BNS_GraphicsEngine();
}

void BNS_GraphicsEngine::release()
{
	if (!BNS_GraphicsEngine::m_engine)
		return;
	delete BNS_GraphicsEngine::m_engine;
}
