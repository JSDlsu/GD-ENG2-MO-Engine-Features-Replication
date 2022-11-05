#include "BNS_AppWindow.h"
#include <Windows.h>

#include "Cube.h"
#include "Matrix4x4.h"
#include "InputSystem.h"
#include "BNS_EngineTime.h"
#include "GameObjectManager.h"
#include "PrimitiveCreation.h"
#include <vector>
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_GraphicsEngine.h"
#include "PassRender.h"
#include "Plane.h"
#include "SwapChain.h"


BNS_AppWindow::BNS_AppWindow()
{
}

BNS_AppWindow::~BNS_AppWindow()
{
}

void BNS_AppWindow::onCreate()
{
	Window::onCreate();

	// create cameras
	BNS_CameraHandler::Initialize();


	RECT rc = this->getClientWindowRect();
	m_swap_chain = BNS_GraphicsEngine::get()->getRenderSystem()->CreateSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);

	UIManager::Initialize(m_hwnd);
	
	// BNS_Color Coords
	Vector3D color_list1[] =
	{
		//FRONT FACE
		BNS_Color::Black,
		BNS_Color::Red,
		BNS_Color::White,
		BNS_Color::Yellow,
		//BACK FACE
		BNS_Color::Black,
		BNS_Color::Red,
		BNS_Color::White,
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

	Cube* cube1 = new Cube("cube1", BNS_ObjectTypes::CUBE);
	cube1->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR);
	cube1->SetVertexShader(BNS_VertexShaderType::COLOR);
	cube1->SetPixelShader(BNS_PixelShaderType::COLOR);
	cube1->SetPosition(Vector3D{ 0, 1, 0 });
	cube1->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr1(cube1);
	GameObjectManager::get()->objectList.push_back(temp_ptr1);

	Cube* cube2 = new Cube("cube2", BNS_ObjectTypes::CUBE);
	cube2->SetVertex_Index_Buffer(BNS_VertexShaderType::TEXTURE);
	cube2->SetVertexShader(BNS_VertexShaderType::TEXTURE);
	cube2->SetPixelShader(BNS_PixelShaderType::TEXTURE);
	cube2->SetMesh(L"Assets\\Meshes\\teapot.obj");
	cube2->SetTexture(L"Assets\\Textures\\brick.png");
	cube2->SetPosition(Vector3D{ 0, 0, 0 });
	cube2->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr2(cube2);
	GameObjectManager::get()->objectList.push_back(temp_ptr2);
	
	Cube* cube3 = new Cube("cube3", BNS_ObjectTypes::CUBE);
	cube3->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR_LERP, colorData1);
	cube3->SetVertexShader(BNS_VertexShaderType::COLOR_LERP);
	cube3->SetPixelShader(BNS_PixelShaderType::COLOR_LERP);
	cube3->SetPosition(Vector3D{ 0, 0, 1 });
	cube3->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr3(cube3);
	GameObjectManager::get()->objectList.push_back(temp_ptr3);

	Cube* cube4 = new Cube("cube4", BNS_ObjectTypes::CUBE);
	cube4->SetVertex_Index_Buffer(BNS_VertexShaderType::COLOR_LERP, colorData1);
	cube4->SetVertexShader(BNS_VertexShaderType::COLOR_LERP);
	cube4->SetPixelShader(BNS_PixelShaderType::COLOR_LERP);
	cube4->SetPosition(Vector3D{ 0, 0, -1 });
	cube4->SetAlpha(0.5f);
	AGameObjectPtr temp_ptr4(cube4);
	GameObjectManager::get()->objectList.push_back(temp_ptr4);

	// create blenderPtr
	m_blender = BNS_GraphicsEngine::get()->getRenderSystem()->CreateBlender();

}

// updating our constant buffers
void BNS_AppWindow::update()
{
	// Call each object's constant buffer in the scene
	std::vector<AGameObjectPtr>::iterator i;
	for (i = GameObjectManager::get()->objectList.begin(); i != GameObjectManager::get()->objectList.end(); ++i)
	{
		//std::static_pointer_cast<Cube>(*i)->m_cb->update(BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext(), &cc);
		if ((*i) != nullptr)
			(*i)->Update(BNS_EngineTime::getDeltaTime(), this);
	}

}

void BNS_AppWindow::onUpdate()
{
	Window::onUpdate();

	// run the update for the InputSystem
	InputSystem::get()->update(m_hwnd);

	//CLEAR THE RENDER TARGET 
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain,
		0.5f, 1.0f, 0.5f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	update();

	// PassRender; Draw objects in order
	// Opaque objects are draw first
	PassRender<OpaqueFilterPolicy, FrontToBackPolicy> opaquePass;
	opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());
	// Transparent objects are draw last
	PassRender<TransparencyFilterPolicy, BackToFrontPolicy> transparencyPass;
	transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCameraMatrix());

	UIManager::GetInstance()->DrawAllUIScreens();

	m_swap_chain->present(true);
}

void BNS_AppWindow::onDestroy()
{
	Window::onDestroy();

	UIManager::Release();
}

void BNS_AppWindow::onFocus()
{

}

void BNS_AppWindow::onKillFocus()
{

}

