#pragma once
#include "BNS_VertexShaderManager.h"
#include "BNS_PixelShaderManager.h"

// Singleton class
// initializes the Vertex and Pixel Shaders
class BNS_ShaderEngine
{
private:
	//Initialize the BNS_GraphicsEngine and DirectX 11 Device
	BNS_ShaderEngine();
	//Release all the resources loaded
	~BNS_ShaderEngine();
public:
	BNS_VertexShaderManager* getVertexShaderManager();
	BNS_PixelShaderManager* getPixelShaderManager();
private:

public:
	static BNS_ShaderEngine* get();
	static void create();
	static void release();
private:
	BNS_VertexShaderManager* m_vertexShader_manager = nullptr;
	BNS_PixelShaderManager* m_pixelShader_manager = nullptr;
	static BNS_ShaderEngine* m_engine;
private:
	friend class BNS_VertexBuffer;
};

