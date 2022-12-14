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
#include "BNS_SkyBox.h"
#include "BNS_SwapChain.h"
#include "BNS_TransformSystem.h"
#include "BNS_EngineBackend.h"
#include "BNS_ActionHistory.h"


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
	BNS_EngineBackend::initialize();

	BNS_EngineBackend::getInstance()->setMode(BNS_EngineBackend::EDITOR);
	BNS_ActionHistory::Initialize();


	// create swap chain
	RECT rc = this->getClientWindowRect();
	m_swap_chain = BNS_GraphicsEngine::get()->getRenderSystem()->CreateSwapChain(
		this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	// create blenderPtr
	m_blender = BNS_GraphicsEngine::get()->getRenderSystem()->CreateBlender();
	// create GAME SCENE views
	m_scene_views[0] = BNS_GraphicsEngine::get()->getRenderSystem()->
		CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	m_scene_views[1] = BNS_GraphicsEngine::get()->getRenderSystem()->
		CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	m_scene_views[2] = BNS_GraphicsEngine::get()->getRenderSystem()->
		CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	m_scene_views[3] = BNS_GraphicsEngine::get()->getRenderSystem()->
		CreateRenderToTexture(rc.right - rc.left, rc.bottom - rc.top);
	// create the UI manager
	BNS_UIManager::Initialize(this, m_hwnd, m_scene_views);
	// Create base skybox
	BNS_PrimitiveCreation::Instance()->CreateSkyBox();
	
}

void BNS_AppWindow::render()
{
	{
		// CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[0], 0.5f, 1.0f, 0.5f, 1);
		// Update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}
		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	{
		// CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[1], 0.5f, 1.0f, 0.5f, 1);
		// Update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}
		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	{
		// CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[2], 0.5f, 1.0f, 0.5f, 1);
		// Update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}
		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	{
		// CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[3], 0.5f, 1.0f, 0.5f, 1);
		// Update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}
		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	//CLEAR THE RENDER TARGET 
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, 0.5f, 1.0f, 0.5f, 1);
	//SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setViewportSize
	(rc.right - rc.left, rc.bottom - rc.top);
	
	BNS_UIManager::GetInstance()->DrawAllUIScreens();

	m_swap_chain->present(true);
}

void BNS_AppWindow::onUpdate()
{
	// 1st render texture
	{
		BNS_Window::onUpdate();
		//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[0], 0.5f, 1.0f, 0.5f, 1);
		// update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		Vector3D camPos = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetMatrix().getTranslation();
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}
	
		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	// 2nd render texture
	{
		BNS_Window::onUpdate();
		//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[1], 0.5f, 1.0f, 0.5f, 1);
		// update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		Vector3D camPos = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetMatrix().getTranslation();
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}

		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	// 3rd render texture
	{
		BNS_Window::onUpdate();
		//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[2], 0.5f, 1.0f, 0.5f, 1);
		// update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		Vector3D camPos = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetMatrix().getTranslation();
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		BNS_EngineBackend* backend = BNS_EngineBackend::getInstance();
		if (backend->getMode() == BNS_EngineBackend::EditorMode::PLAY) {
			// update for physics engine
			BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::EDITOR) {
			// update for transforms engine
			BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();

		}
		else if (backend->getMode() == BNS_EngineBackend::EditorMode::PAUSED) {
			if (backend->insideFrameStep()) {
				// update for physics engine
				BNS_BaseComponentSystem::GetInstance()->GetPhysicsSystem()->UpdateAllComponents();
				// update for transforms engine
				BNS_BaseComponentSystem::GetInstance()->GetTransformSystem()->UpdateAllComponents();
				backend->endFrameStep();
			}
		}

		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}
	// 4th render texture
	{
		BNS_Window::onUpdate();
		//CLEAR THE RENDER TARGET FOR RENDER_TO_TEXTURE
		BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
		(m_swap_chain, m_scene_views[3], 0.5f, 1.0f, 0.5f, 1);
		// update camera
		BNS_CameraHandler::GetInstance()->GetSceneCamera()->Update(BNS_EngineTime::getDeltaTime(), this);
		Vector3D camPos = BNS_CameraHandler::GetInstance()->GetSceneCamera()->GetMatrix().getTranslation();
		// run the update for the BNS_InputSystem
		BNS_InputSystem::get()->update(m_hwnd);

		// Update SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Update(BNS_EngineTime::getDeltaTime());
		// update renderstate (back)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(false);
		// BNS_PassRender; Draw objects in order
		// Opaque objects are draw first
		BNS_PassRender<BNS_OpaqueFilterPolicy, BNS_FrontToBackPolicy> opaquePass;
		opaquePass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// Transparent objects are draw last
		BNS_PassRender<BNS_TransparencyFilterPolicy, BNS_BackToFrontPolicy> transparencyPass;
		transparencyPass.Render(m_blender, BNS_CameraHandler::GetInstance()->GetSceneCamera());
		// update renderstate (front)
		BNS_GraphicsEngine::get()->getRenderSystem()->SetRasterizerState(true);
		// Draw SkyBox
		BNS_GameObjectManager::get()->GetSkyBox()->Draw(m_blender);
	}

	// CLEAR THE RENDER TARGET 
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->clearRenderTargetColor
	(m_swap_chain, 0.5f, 1.0f, 0.5f, 1);
	// SET VIEWPORT OF RENDER TARGET IN WHICH WE HAVE TO DRAW
	RECT rc = this->getClientWindowRect();
	BNS_GraphicsEngine::get()->getRenderSystem()->GetImmediateDeviceContext()->setViewportSize
	(rc.right - rc.left, rc.bottom - rc.top);

	BNS_UIManager::GetInstance()->DrawAllUIScreens();

	m_swap_chain->present(true);

}

void BNS_AppWindow::onDestroy()
{
	m_swap_chain->setFullScreen(false, 1, 1);

	BNS_UIManager::Release();
	// destroy physics
	//BNS_BaseComponentSystem::Destroy();
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
	m_scene_views[BNS_CameraHandler::GetInstance()->currentCamIndex]->resize(rc.right, rc.bottom);
	render();
}

