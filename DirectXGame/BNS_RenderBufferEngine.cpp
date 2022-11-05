#include "BNS_RenderBufferEngine.h"
#include <exception>
#include <iostream>

BNS_RenderBufferEngine* BNS_RenderBufferEngine::m_engine = nullptr;

BNS_RenderBufferEngine::BNS_RenderBufferEngine()
{
	try
	{
		// instantiate our BNS_VertexShaderManager
		m_input_layout_manager = new BNS_InputLayoutManager();
	}
	catch (...)
	{
		throw std::exception("BNS_InputLayoutManager not created successfully");
	}
}

BNS_RenderBufferEngine::~BNS_RenderBufferEngine()
{
	BNS_RenderBufferEngine::m_engine = nullptr;
	delete m_input_layout_manager;
}

BNS_InputLayoutManager* BNS_RenderBufferEngine::getInputLayoutManager()
{
	return m_input_layout_manager;
}

BNS_RenderBufferEngine* BNS_RenderBufferEngine::get()
{
	return m_engine;
}

void BNS_RenderBufferEngine::create()
{
	if (BNS_RenderBufferEngine::m_engine)
		throw std::exception("BNS_RenderBufferEngine already created");
	BNS_RenderBufferEngine::m_engine = new BNS_RenderBufferEngine();
}

void BNS_RenderBufferEngine::release()
{
	if (!BNS_RenderBufferEngine::m_engine)
		return;
	delete BNS_RenderBufferEngine::m_engine;
}
