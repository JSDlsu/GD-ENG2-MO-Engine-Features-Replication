#include "AppWindow.h"
#include <Windows.h>

#include "Cube.h"
#include "Line.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "EngineTime.h"
#include "GameObjectManager.h"
#include "PrimitiveCreation.h"
#include <vector>
#include "Camera.h"
#include "CameraHandler.h"
#include "GraphicsEngine.h"
#include "PassRender.h"
#include "Plane.h"
#include "SwapChain.h"
#include <DirectXMath.h>


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

	RECT rc = this->getClientWindowRect();
	m_swap_chain = GraphicsEngine::get()->getRenderSystem()->createSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	InputSystem::get()->addListener(this);
	
	// Color Coords
	Vector3D color_list1[] =
	{
		//FRONT FACE
		Color::Black,
		Color::Red,
		Color::White,
		Color::Yellow,
		//BACK FACE
		Color::Black,
		Color::Red,
		Color::White,
		Color::Yellow,
	};

	// Color Coords
	Vector3D color_list2[] =
	{
		//FRONT FACE
		Color::Gray,
		Color::Blue,
		Color::Green,
		Color::Purple,
		//BACK FACE
		Color::Gray,
		Color::Blue,
		Color::Green,
		Color::Purple,
	};
	PC_Cube_ColorData colorData1;
	memcpy(colorData1.color_list_1, color_list1, sizeof(color_list1));
	memcpy(colorData1.color_list_2, color_list2, sizeof(color_list2));

	Cube* cube1 = new Cube("cube1", ObjectTypes::CUBE);
	cube1->SetVertex_Index_Buffer(VertexShaderType::COLOR);
	cube1->SetVertexShader(VertexShaderType::COLOR);
	cube1->SetPixelShader(PixelShaderType::COLOR);
	cube1->SetPosition(Vector3D{ 0, 1, 0 });
	cube1->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr1(cube1);
	GameObjectManager::get()->objectList.push_back(temp_ptr1);

	Cube* cube2 = new Cube("cube2", ObjectTypes::CUBE);
	cube2->SetVertex_Index_Buffer(VertexShaderType::TEXTURE);
	cube2->SetVertexShader(VertexShaderType::TEXTURE);
	cube2->SetPixelShader(PixelShaderType::TEXTURE);
	cube2->SetMesh(L"Assets\\Meshes\\teapot.obj");
	cube2->SetTexture(L"Assets\\Textures\\brick.png");
	cube2->SetPosition(Vector3D{ 0, 0, 0 });
	cube2->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr2(cube2);
	GameObjectManager::get()->objectList.push_back(temp_ptr2);
	
	Cube* cube3 = new Cube("cube3", ObjectTypes::CUBE);
	cube3->SetVertex_Index_Buffer(VertexShaderType::COLOR_LERP, colorData1);
	cube3->SetVertexShader(VertexShaderType::COLOR_LERP);
	cube3->SetPixelShader(PixelShaderType::COLOR_LERP);
	cube3->SetPosition(Vector3D{ 0, 0, 1 });
	cube3->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr3(cube3);
	GameObjectManager::get()->objectList.push_back(temp_ptr3);

	Cube* cube4 = new Cube("cube4", ObjectTypes::CUBE);
	cube4->SetVertex_Index_Buffer(VertexShaderType::COLOR_LERP, colorData1);
	cube4->SetVertexShader(VertexShaderType::COLOR_LERP);
	cube4->SetPixelShader(PixelShaderType::COLOR_LERP);
	cube4->SetPosition(Vector3D{ 0, 0, -1 });
	cube4->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr4(cube4);
	GameObjectManager::get()->objectList.push_back(temp_ptr4);

	Line* line1 = new Line("line1", ObjectTypes::LINE);
	line1->SetVertex_Index_Buffer(VertexShaderType::COLOR);
	line1->SetVertexShader(VertexShaderType::COLOR);
	line1->SetPixelShader(PixelShaderType::COLOR);
	line1->SetPosition(Vector3D{ 2, 5, 0 });
	line1->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr5(line1);
	GameObjectManager::get()->objectList.push_back(temp_ptr5);

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
	opaquePass.Render(m_blender, CameraHandler::GetInstance()->GetSceneCameraMatrix());
	// Transparent objects are draw last
	PassRender<TransparencyFilterPolicy, BackToFrontPolicy> transparencyPass;
	transparencyPass.Render(m_blender, CameraHandler::GetInstance()->GetSceneCameraMatrix());

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

void AppWindow::onKeyDown(int key)
{
}

void AppWindow::onKeyUp(int key)
{
}

void AppWindow::onMouseMove(const Point& mouse_pos)
{
}

void AppWindow::onLeftMouseDown(const Point& delta_mouse_pos)
{
	Pick(delta_mouse_pos);
}

void AppWindow::onLeftMouseUp(const Point& delta_mouse_pos)
{
}

void AppWindow::onRightMouseDown(const Point& delta_mouse_pos)
{
}

void AppWindow::onRightMouseUp(const Point& delta_mouse_pos)
{
}

void AppWindow::Pick(const Point& delta_mouse_pos)
{
	Matrix4x4 viewMatrixInverse;
	PickingRay ray;
	

	float width = this->getClientWindowRect().right - this->getClientWindowRect().left;
	float height = this->getClientWindowRect().bottom - this->getClientWindowRect().top;
	float aspectRatio = (float)(Window::WIDTH) / (float)(Window::HEIGHT);

	float vx = (2.0f * delta_mouse_pos.m_x / width - 1.0f) / CameraHandler::GetInstance()->GetSceneCameraProjectionMatrix().m_mat[0][0];
	float vy = (-2.0f * delta_mouse_pos.m_y / height + 1.0f) / CameraHandler::GetInstance()->GetSceneCameraProjectionMatrix().m_mat[1][1];

	ray.origin = CameraHandler::GetInstance()->GetSceneCameraMatrix().getTranslation();
	ray.direction = Vector3D(vx, vy, 1.0f);

	viewMatrixInverse = CameraHandler::GetInstance()->GetSceneCameraViewMatrix();
	viewMatrixInverse.inverse();

	ray.origin = Matrix4x4::Vector3Transform(ray.origin, viewMatrixInverse);
	ray.direction = Matrix4x4::Vector3TransformNormal(ray.direction, viewMatrixInverse);
	ray.direction = Vector3D::getUnitVector(ray.direction);

	std::cout << ray.direction.m_x << ", " << ray.direction.m_y << ", " << ray.direction.m_z << std::endl;
	
}
