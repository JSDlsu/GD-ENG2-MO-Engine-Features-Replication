#pragma once
#include "VertexShaderManager.h"
#include "PixelShaderManager.h"

// Singleton class
// initializes the Vertex and Pixel Shaders
class ShaderEngine
{
private:
	//Initialize the GraphicsEngine and DirectX 11 Device
	ShaderEngine();
	//Release all the resources loaded
	~ShaderEngine();
public:
	VertexShaderManager* getVertexShaderManager();
	PixelShaderManager* getPixelShaderManager();
private:

public:
	static ShaderEngine* get();
	static void create();
	static void release();
private:
	VertexShaderManager* m_vertexShader_manager = nullptr;
	PixelShaderManager* m_pixelShader_manager = nullptr;
	static ShaderEngine* m_engine;
private:
	friend class VertexBuffer;
};

