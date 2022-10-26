#include "GraphicsEngine.h"
#include "RenderSystem.h"
#include <exception>
#include <iostream>

GraphicsEngine* GraphicsEngine::m_engine = nullptr;

GraphicsEngine::GraphicsEngine()
{
	try
	{
		// instantiate our RenderSystem
		m_render_system = new RenderSystem();
	}
	catch (...)
	{
		throw std::exception("GraphicsEngine not created successfully");
	}
	try
	{
		// instantiate our TextureManager
		m_tex_manager = new TextureManager();
	}
	catch (...)
	{
		throw std::exception("TextureManager not created successfully");
	}
	try
	{
		// instantiate our TextureManager
		m_mesh_manager = new MeshManager();
	}
	catch (...)
	{
		throw std::exception("MeshManager not created successfully");
	}
	try
	{
		// instantiate our VertexShaderManager
		m_vertexShader_manager = new VertexShaderManager(m_render_system);
	}
	catch (...)
	{
		throw std::exception("VertexShaderManager not created successfully");
	}
	try
	{
		// instantiate our PixelShaderManager
		m_pixelShader_manager = new PixelShaderManager();
	}
	catch (...)
	{
		throw std::exception("PixelShaderManager not created successfully");
	}
}

GraphicsEngine::~GraphicsEngine()
{
	GraphicsEngine::m_engine = nullptr;
	delete m_pixelShader_manager;
	delete m_vertexShader_manager;
	delete m_mesh_manager;
	delete m_tex_manager;
	delete m_render_system;
}

RenderSystem* GraphicsEngine::getRenderSystem()
{
	return m_render_system;
}

TextureManager* GraphicsEngine::getTextureManager()
{
	return m_tex_manager;
}

MeshManager* GraphicsEngine::getMeshManager()
{
	return m_mesh_manager;
}

VertexShaderManager* GraphicsEngine::getVertexShaderManager()
{
	return m_vertexShader_manager;
}

PixelShaderManager* GraphicsEngine::getPixelShaderManager()
{
	return m_pixelShader_manager;
}

GraphicsEngine* GraphicsEngine::get()
{
	return m_engine;
}

void GraphicsEngine::create()
{
	if (GraphicsEngine::m_engine) 
		throw std::exception("GraphicsEngine already created");
	GraphicsEngine::m_engine = new GraphicsEngine();
}

void GraphicsEngine::release()
{
	if (!GraphicsEngine::m_engine)
		return;
	delete GraphicsEngine::m_engine;
}
