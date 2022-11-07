#include "BNS_AppWindow.h"
#include <Windows.h>

#include "BNS_Cube.h"
#include "Matrix4x4.h"
#include "BNS_InputSystem.h"
#include "BNS_EngineTime.h"
#include "BNS_GameObjectManager.h"
#include "BNS_PrimitiveCreation.h"
#include <vector>
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_PassRender.h"
#include "BNS_Plane.h"
#include "BNS_SwapChain.h"


BNS_AppWindow::BNS_AppWindow()
{
}

BNS_AppWindow::~BNS_AppWindow()
{
}

float BNS_AppWindow::randomFloat(float x, float y)
{
	return x + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (y - x)));
}

void BNS_AppWindow::onCreate()
{
	BNS_Window::onCreate();

	// create cameras
	BNS_CameraHandler::Initialize();


	RECT rc = this->getClientWindowRect();
	m_swap_chain = BNS_GraphicsEngine::get()->getRenderSystem()->CreateSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	// create blenderPtr
	m_blender = BNS_GraphicsEngine::get()->getRenderSystem()->CreateBlender();
	// create GAME SCENE view
	//m_game_scene = BNS_GraphicsEngine::get()->getRenderSystem()->CreateRenderToTexture(512, 512);
	m_game_scene = BNS_GraphicsEngine::get()->getRenderSystem()->CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	// create the UI manager
	BNS_UIManager::Initialize(m_hwnd, m_game_scene);
	
	// BNS_Color Coords
	Vector3D color_list1[] =
	{
		//FRONT FACE
		BNS_Color::Blue,
		BNS_Color::Red,
		BNS_Color::Green,
		BNS_Color::Yellow,
		//BACK FACE
		BNS_Color::Blue,
		BNS_Color::Red,
		BNS_Color::Green,
		BNS_Color::Yellow,
	};

	// BNS_Color Coords
	Vector3D color_list2[] =
	{
		//FRONT FACE
		BNS_Color::Gray,
		BNS_Color::Blue,
		BNS_Color::Green,
		BNS_Color::Purple,
		//BACK FACE
		BNS_Color::Gray,
		BNS_Color::Blue,
		BNS_Color::Green,
		BNS_Color::Purple,
	};
	BNS_PC_Cube_ColorData colorData1;
	memcpy(colorData1.color_list_1, color_list1, sizeof(color_list1));
	memcpy(colorData1.color_list_2, color_list2, sizeof(color_list2));

#define PLAY 0
#if PLAY == 0
	BNS_Cube* cube1 = new BNS_Cube("cube3", BNS_ObjectTypes::CUBE);
	cube1->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR, colorData1);
	cube1->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	cube1->SetVertexShader(BNS_VertexShaderType::COLOR);
	cube1->SetPixelShader(BNS_PixelShaderType::COLOR);
	cube1->SetPosition(Vector3D{ 0, 0.0f, 0 });
	cube1->SetAlpha(1.0f);
	AGameObjectPtr temp_ptr1(cube1);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr1);

	BNS_Cube* cube2 = new BNS_Cube("cube3", BNS_ObjectTypes::CUBE);
	cube2->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	cube2->SetVertexShader(BNS_VertexShaderType::COLOR);
	cube2->SetPixelShader(BNS_PixelShaderType::COLOR);
	cube2->SetPosition(Vector3D{ -1.5f, 2.0f, 0 });
	cube2->SetAlpha(1.0f);
	AGameObjectPtr temp_ptr2(cube2);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr2);

	BNS_Cube* cube3 = new BNS_Cube("cube3", BNS_ObjectTypes::CUBE);
	cube3->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	cube3->SetVertexShader(BNS_VertexShaderType::COLOR);
	cube3->SetPixelShader(BNS_PixelShaderType::COLOR);
	cube3->SetPosition(Vector3D{ -1.5f, 3.0f, -2.0f });
	cube3->SetAlpha(1.0f);
	AGameObjectPtr temp_ptr3(cube3);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr3);

	BNS_Plane* plane = new BNS_Plane("cube3", BNS_ObjectTypes::PLANE);
	plane->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	plane->SetVertexShader(BNS_VertexShaderType::COLOR);
	plane->SetPixelShader(BNS_PixelShaderType::COLOR);
	plane->SetScale(Vector3D{ 10.0f, 0.01f, 10.0f });
	plane->SetPosition(Vector3D{ 0.0f, -1.0f, 0 });
	plane->SetAlpha(1.0f);
	AGameObjectPtr temp_ptr4(plane);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr4);
#elif PLAY == 1
	BNS_Cube* cube1 = new BNS_Cube("cube1", BNS_ObjectTypes::CUBE);
	cube1->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	cube1->SetVertexShader(BNS_VertexShaderType::COLOR);
	cube1->SetPixelShader(BNS_PixelShaderType::COLOR);
	cube1->SetPosition(Vector3D{ 0, 1, 0 });
	cube1->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr1(cube1);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr1);

	BNS_Cube* cube2 = new BNS_Cube("cube2", BNS_ObjectTypes::CUBE);
	cube2->SetVertex_Index_Buffer(BNS_VertexShaderType::TEXTURE);
	cube2->SetVertexShader(BNS_VertexShaderType::TEXTURE);
	cube2->SetPixelShader(BNS_PixelShaderType::TEXTURE);
	cube2->SetMesh(L"Assets\\Meshes\\teapot.obj");
	cube2->SetTexture(L"Assets\\Textures\\brick.png");
	cube2->SetPosition(Vector3D{ 0, 0, 0 });
	cube2->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr2(cube2);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr2);

	BNS_Cube* cube3 = new BNS_Cube("cube3", BNS_ObjectTypes::CUBE);
	cube3->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR_LERP, colorData1);
	cube3->SetVertexShader(BNS_VertexShaderType::COLOR_LERP);
	cube3->SetPixelShader(BNS_PixelShaderType::COLOR_LERP);
	cube3->SetPosition(Vector3D{ 0, 0, 1 });
	cube3->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr3(cube3);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr3);

	BNS_Cube* cube4 = new BNS_Cube("cube4", BNS_ObjectTypes::CUBE);
	cube4->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR_LERP, colorData1);
	cube4->SetVertexShader(BNS_VertexShaderType::COLOR_LERP);
	cube4->SetPixelShader(BNS_PixelShaderType::COLOR_LERP);
	cube4->SetPosition(Vector3D{ 0, 0, -1 });
	cube4->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr4(cube4);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr4);

	BNS_Plane* plane1 = new BNS_Plane("plane1", BNS_ObjectTypes::PLANE);
	plane1->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	plane1->SetVertexShader(BNS_VertexShaderType::COLOR);
	plane1->SetPixelShader(BNS_PixelShaderType::COLOR);
	plane1->SetPosition(Vector3D{ 0, 0, -1 });
	plane1->SetAlpha(1.0f);
	AGameObjectPtr temp_ptr5(plane1);
	BNS_GameObjectManager::get()->objectList.push_back(temp_ptr5);
#endif


}

// updating our constant buffers
void BNS_AppWindow::update()
{
	// Call each object's constant buffer in the scene
	std::vector<AGameObjectPtr>::iterator i;
	for (i = BNS_GameObjectManager::get()->objectList.begin(); i != BNS_GameObjectManager::get()->objectList.end(); ++i)
	{
		//std::static_pointer_cast<BNS_Cube>(*i)->m_cb->update(BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);
		if ((*i) != nullptr)
			(*i)->Update(BNS_EngineTime::getDeltaTime(), this);
	}

}

void BNS_AppWindow::onUpdate()
{
	BNS_Window::onUpdate();

	// run the update for the BNS_InputSystem
	BNS_InputSystem::get()->update(m_hwnd);

	//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, m_game_scene, 0.5f, 1.0f, 0.5f, 1);

	// BNS_PassRender; Draw objects in order
	// Opaque objects are draw first
	BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
	opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());
	// Transparent objects are draw last
	BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
	transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());

	//CLEAR THE RENDER TARGET 
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, 0.5f, 1.0f, 0.5f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setViewportSize
	(rc.right - rc.left, rc.bottom - rc.top);

	update();
	/*
	// BNS_PassRender; Draw objects in order
	// Opaque objects are draw first
	opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());
	// Transparent objects are draw last
	transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());
	*/

	BNS_UIManager::GetInstance()->DrawAllUIScreens();

	m_swap_chain->present(true);
}

void BNS_AppWindow::onDestroy()
{
	BNS_Window::onDestroy();

	BNS_UIManager::Release();
}

void BNS_AppWindow::onFocus()
{

}

void BNS_AppWindow::onKillFocus()
{

}

