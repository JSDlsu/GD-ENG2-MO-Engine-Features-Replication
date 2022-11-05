#pragma once
#include "BNS_Prerequisites.h"
#include "BNS_InputLayoutManager.h"

// Singleton class
// initializes the Vertex and Pixel Shaders
class BNS_RenderBufferEngine
{
private:
	//Initialize the BNS_GraphicsEngine and DirectX 11 Device
	BNS_RenderBufferEngine();
	//Release all the resources loaded
	~BNS_RenderBufferEngine();
public:
	BNS_InputLayoutManager* getInputLayoutManager();
private:

public:
	static BNS_RenderBufferEngine* get();
	static void create();
	static void release();
private:
	BNS_InputLayoutManager* m_input_layout_manager = nullptr;
	static BNS_RenderBufferEngine* m_engine;
private:
	friend class BNS_VertexBuffer;
};

