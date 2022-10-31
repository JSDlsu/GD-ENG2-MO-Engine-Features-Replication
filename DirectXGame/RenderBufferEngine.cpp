#include "RenderBufferEngine.h"
#include <exception>
#include <iostream>

RenderBufferEngine* RenderBufferEngine::m_engine = nullptr;

RenderBufferEngine::RenderBufferEngine()
{
	try
	{
		// instantiate our VertexShaderManager
		m_input_layout_manager = new InputLayoutManager();
	}
	catch (...)
	{
		throw std::exception("InputLayoutManager not created successfully");
	}
}

RenderBufferEngine::~RenderBufferEngine()
{
	RenderBufferEngine::m_engine = nullptr;
	delete m_input_layout_manager;
}

InputLayoutManager* RenderBufferEngine::getInputLayoutManager()
{
	return m_input_layout_manager;
}

RenderBufferEngine* RenderBufferEngine::get()
{
	return m_engine;
}

void RenderBufferEngine::create()
{
	if (RenderBufferEngine::m_engine)
		throw std::exception("RenderBufferEngine already created");
	RenderBufferEngine::m_engine = new RenderBufferEngine();
}

void RenderBufferEngine::release()
{
	if (!RenderBufferEngine::m_engine)
		return;
	delete RenderBufferEngine::m_engine;
}
