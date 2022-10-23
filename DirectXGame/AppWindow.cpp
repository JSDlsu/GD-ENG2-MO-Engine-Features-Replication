#include "AppWindow.h"
#include <Windows.h>

#include "Cube.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "PrimitiveCreation.h"
#include <vector>

#include "Camera.h"
#include "CameraHandler.h"
#include "PassRender.h"
#include "Plane.h"


AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();

	// create cameras
	CameraHandler::Initialize();

	// hides the cursor
	InputSystem::get()->showCursor(false);

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// instantiate a cube and texture
	Cube* cube = new Cube("cube1", ObjectTypes::CUBE);
	cube->SetTexture(L"Assets\\Textures\\wood.jpg");
	AGameObjectPtr temp_ptr(cube);

	// instantiate a cube and texture
	Cube* cube1 = new Cube("cube2", ObjectTypes::CUBE);
	cube1->SetTexture(L"Assets\\Textures\\coat.png");
	AGameObjectPtr temp_ptr2(cube1);

	// instantiate a mesh from cube and texture
	Cube* cube2 = new Cube("cube3", ObjectTypes::CUBE);
	cube2->SetMesh(L"Assets\\Meshes\\teapot.obj");
	cube2->SetTexture(L"Assets\\Textures\\brick.png");
	AGameObjectPtr temp_ptr3(cube2);

	// instantiate a cube and texture
	Cube* cube3 = new Cube("cube4", ObjectTypes::CUBE);
	cube3->SetTexture(L"Assets\\Textures\\coat.png");
	AGameObjectPtr temp_ptr4(cube3);

	// instantiate a cube and texture
	Plane* plane = new Plane("plane1", ObjectTypes::PLANE);
	plane->SetTexture(L"Assets\\Textures\\wood.jpg");
	AGameObjectPtr temp_ptr5(plane);

	cube->SetScale(Vector3D{ 0.5f, 0.5f, 0.5f });
	cube->SetPosition(Vector3D{ 1, 0, 0 });
	cube1->SetPosition(Vector3D{ 0, 0, -1 });
	cube3->SetPosition(Vector3D{ 0, 0, 1 });
	plane->SetPosition(0, -1.0f, 0);
	cube->SetAlpha(1.0f);
	cube1->SetAlpha(0.5f);
	cube2->SetAlpha(1.0f);
	cube3->SetAlpha(0.2f);
	plane->SetAlpha(1.0f);
	// add the objects to our manager
	GameObjectManager::get()->objectList.push_back(temp_ptr);
	GameObjectManager::get()->objectList.push_back(temp_ptr2);
	GameObjectManager::get()->objectList.push_back(temp_ptr3);
	GameObjectManager::get()->objectList.push_back(temp_ptr4);
	GameObjectManager::get()->objectList.push_back(temp_ptr5);

	// gets the byte code and size of the vertex shader
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getPixelShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	// after a successful compiling, create the vertex buffer then
	m_vs = GraphicsEngine::get()->getRenderSystem()->createVertexShader(shader_byte_code, size_shader);

	// access the PixelShader.hlsl and compile
	GraphicsEngine::get()->getRenderSystem()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->getRenderSystem()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->getRenderSystem()->releaseCompiledShader();

	// create blenderPtr
	m_blender = GraphicsEngine::get()->getRenderSystem()->createBlender();

}

// updating our constant buffers
void AppWindow::update()
{
	// Call each object's constant buffer in the scene
	std::vector<AGameObjectPtr>::iterator i;
	for (i = GameObjectManager::get()->objectList.begin(); i != GameObjectManager::get()->objectList.end(); ++i)
	{
		//std::static_pointer_cast<Cube>(*i)->m_cb->update(GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext(), &cc);
		if ((*i) != nullptr)
			(*i)->Update(EngineTime::getDeltaTime(), this);
	}

}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	// run the update for the InputSystem
	InputSystem::get()->update();

	//CLEAR THE RENDER TARGET 
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.5f, 1.0f, 0.5f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	// PassRender; Draw objects in order
	// Opaque objects are draw first
	PassRender<OpaqueFilterPolicy, FrontToBackPolicy> opaquePass;
	opaquePass.Render(m_vs, m_ps, m_blender, CameraHandler::GetInstance()->GetSceneCameraMatrix());
	// Transparent objects are draw last
	PassRender<TransparencyFilterPolicy, BackToFrontPolicy> transparencyPass;
	transparencyPass.Render(m_vs, m_ps, m_blender, CameraHandler::GetInstance()->GetSceneCameraMatrix());

	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();
}

void AppWindow::onFocus()
{

}

void AppWindow::onKillFocus()
{

}

