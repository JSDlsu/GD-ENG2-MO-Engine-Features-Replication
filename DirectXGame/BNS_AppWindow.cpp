#include "BNS_AppWindow.h"
#include <Windows.h>

#include "BNS_Cube.h"
#include "Matrix4x4.h"
#include "BNS_InputSystem.h"
#include "BNS_EngineTime.h"
#include "BNS_GameObjectManager.h"
#include "BNS_PrimitiveCreation.h"
#include <vector>

#include "BNS_BaseComponentSystem.h"
#include "BNS_Camera.h"
#include "BNS_CameraHandler.h"
#include "BNS_GraphicsEngine.h"
#include "BNS_PassRender.h"
#include "BNS_PhysicsSystem.h"
#include "BNS_Plane.h"
#include "BNS_RenderToTexture.h"
#include "BNS_SwapChain.h"
#include "BNS_Log.h"


BNS_AppWindow::BNS_AppWindow()
{
}

BNS_AppWindow::~BNS_AppWindow()
{
}

void BNS_AppWindow::onCreate()
{
	// create window
	BNS_Window::onCreate();
	// create physics
	BNS_BaseComponentSystem::Initialize();
	// create cameras
	BNS_CameraHandler::Initialize();


	// create swap chain
	RECT rc = this->getClientWindowRect();
	m_swap_chain = BNS_GraphicsEngine::get()->getRenderSystem()->CreateSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	// create blenderPtr
	m_blender = BNS_GraphicsEngine::get()->getRenderSystem()->CreateBlender();
	// create GAME SCENE view
	m_scene_view = BNS_GraphicsEngine::get()->getRenderSystem()->
		CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	// create the UI manager
	BNS_UIManager::Initialize(this, m_hwnd, m_scene_view);

}

void BNS_AppWindow::render()
{
	//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, m_scene_view, 0.5f, 1.0f, 0.5f, 1);
	// update camera
	BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
	// update models
	update();

	// BNS_PassRender; Draw objects in order
	// Opaque objects are draw first
	BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
	opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
	// Transparent objects are draw last
	BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
	transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());

	//CLEAR THE RENDER TARGET 
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, 0.5f, 1.0f, 0.5f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setViewportSize
	(rc.right - rc.left, rc.bottom - rc.top);

	/*
	std::cout << "Cam: X=" << BNS_CameraHandler::GetInstance()->GetSceneCamera().get()->GetLocalPosition().m_x <<
		" Y=" << BNS_CameraHandler::GetInstance()->GetSceneCamera().get()->GetLocalPosition().m_y << " Z=" <<
		BNS_CameraHandler::GetInstance()->GetSceneCamera().get()->GetLocalPosition().m_z << std::endl;
	*/
	/*
	// BNS_PassRender; Draw objects in order
	// Opaque objects are draw first
	opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
	// Transparent objects are draw last
	transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
	*/

	BNS_UIManager::GetInstance()->DrawAllUIScreens();

	m_swap_chain->present(true);
}

// updating our constant buffers
void BNS_AppWindow::update()
{
	// Call each object's constant buffer in the scene
	std::vector<BNS_AGameObject*>::iterator i;
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

	//BNS_Log::get()->DisplayLog(LogType::Display, "test");

	// run the update for the BNS_InputSystem
	BNS_InputSystem::get()->update(m_hwnd);
	// update for physics engine
	BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
	// update for graphics engine
	render();
}

void BNS_AppWindow::onDestroy()
{
	m_swap_chain->setFullScreen(false, 1, 1);

	BNS_UIManager::Release();
	// destroy physics
	BNS_BaseComponentSystem::Destroy();
	BNS_Window::onDestroy();
}

void BNS_AppWindow::onFocus()
{

}

void BNS_AppWindow::onKillFocus()
{

}

void BNS_AppWindow::onSize()
{
	RECT rc = this->getClientWindowRect();
	m_swap_chain->resize(rc.right, rc.bottom);
	m_scene_view->resize(rc.right, rc.bottom);
	render();
}

