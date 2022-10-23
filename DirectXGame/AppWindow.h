#pragma once
#include "Window.h"
#include "GraphicsEngine.h"
#include "SwapChain.h"
#include "DeviceContext.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "InputListener.h"
#include "Matrix4x4.h"

class Cube;
class Plane;
class Camera;
class Mesh;

// displays the main scene; handles the awake,update,end
class AppWindow : public Window
{
public:
	AppWindow();

	void update();

	~AppWindow();

	// Inherited via Window
	virtual void onCreate() override;
	virtual void onUpdate() override;
	virtual void onDestroy() override;
	virtual void onFocus() override;
	virtual void onKillFocus() override;


private:
	SwapChainPtr m_swap_chain;
	VertexShaderPtr m_vs;
	PixelShaderPtr m_ps;
	BlenderPtr m_blender;
private:
private:
	friend class Cube;
	friend class Plane;
	friend class Camera;
	friend class Mesh;
};

