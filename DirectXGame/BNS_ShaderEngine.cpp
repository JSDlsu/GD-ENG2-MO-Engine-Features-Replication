#include "BNS_ShaderEngine.h"
#include <exception>
#include <iostream>

BNS_ShaderEngine* BNS_ShaderEngine::m_engine = nullptr;

BNS_ShaderEngine::BNS_ShaderEngine()
{
	try
	{
		// instantiate our BNS_VertexShaderManager
		m_vertexShader_manager = new BNS_VertexShaderManager();
	}
	catch (...)
	{
		throw std::exception("BNS_VertexShaderManager not created successfully");
	}
	try
	{
		// instantiate our BNS_PixelShaderManager
		m_pixelShader_manager = new BNS_PixelShaderManager();
	}
	catch (...)
	{
		throw std::exception("BNS_PixelShaderManager not created successfully");
	}
}

BNS_ShaderEngine::~BNS_ShaderEngine()
{
	BNS_ShaderEngine::m_engine = nullptr;
	delete m_pixelShader_manager;
	delete m_vertexShader_manager;
}

BNS_VertexShaderManager* BNS_ShaderEngine::getVertexShaderManager()
{
	return m_vertexShader_manager;
}

BNS_PixelShaderManager* BNS_ShaderEngine::getPixelShaderManager()
{
	return m_pixelShader_manager;
}

BNS_ShaderEngine* BNS_ShaderEngine::get()
{
	return m_engine;
}

void BNS_ShaderEngine::create()
{
	if (BNS_ShaderEngine::m_engine)
		throw std::exception("BNS_ShaderEngine already created");
	BNS_ShaderEngine::m_engine = new BNS_ShaderEngine();
}

void BNS_ShaderEngine::release()
{
	if (!BNS_ShaderEngine::m_engine)
		return;
	delete BNS_ShaderEngine::m_engine;
}
