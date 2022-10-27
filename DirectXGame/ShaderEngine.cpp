#include "ShaderEngine.h"
#include <exception>
#include <iostream>

ShaderEngine* ShaderEngine::m_engine = nullptr;

ShaderEngine::ShaderEngine()
{
	try
	{
		// instantiate our VertexShaderManager
		m_vertexShader_manager = new VertexShaderManager();
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

ShaderEngine::~ShaderEngine()
{
	ShaderEngine::m_engine = nullptr;
	delete m_pixelShader_manager;
	delete m_vertexShader_manager;
}

VertexShaderManager* ShaderEngine::getVertexShaderManager()
{
	return m_vertexShader_manager;
}

PixelShaderManager* ShaderEngine::getPixelShaderManager()
{
	return m_pixelShader_manager;
}

ShaderEngine* ShaderEngine::get()
{
	return m_engine;
}

void ShaderEngine::create()
{
	if (ShaderEngine::m_engine)
		throw std::exception("ShaderEngine already created");
	ShaderEngine::m_engine = new ShaderEngine();
}

void ShaderEngine::release()
{
	if (!ShaderEngine::m_engine)
		return;
	delete ShaderEngine::m_engine;
}
