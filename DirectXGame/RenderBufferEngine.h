#pragma once
#include "Prerequisites.h"
#include "InputLayoutManager.h"

// Singleton class
// initializes the Vertex and Pixel Shaders
class RenderBufferEngine
{
private:
	//Initialize the GraphicsEngine and DirectX 11 Device
	RenderBufferEngine();
	//Release all the resources loaded
	~RenderBufferEngine();
public:
	InputLayoutManager* getInputLayoutManager();
private:

public:
	static RenderBufferEngine* get();
	static void create();
	static void release();
private:
	InputLayoutManager* m_input_layout_manager = nullptr;
	static RenderBufferEngine* m_engine;
private:
	friend class VertexBuffer;
};

