#include "BNS_Camera.h"

#include "BNS_AppWindow.h"
#include "BNS_CameraHandler.h"
#include "BNS_EngineTime.h"
#include "BNS_InputSystem.h"
#include "BNS_SwapChain.h"

BNS_Camera::BNS_Camera(std::string name, BNS_ObjectTypes type, int cameraID) : BNS_AGameObject(name, type)
{
	this->cameraID = cameraID;

	if (cameraID == 0)
	{
		m_matrix.setTranslation(Vector3D{ 0.0f, 0.0f, -2.0f });
		SetPosition(Vector3D{ 0.0f, 0.0f, -2.0f });
	}
	else if (cameraID == 1)
	{
		m_matrix.setTranslation(Vector3D{ 0.0f, 0.0f, 2.0f });
		SetPosition(Vector3D{ 0.0f, 0.0f, 2.0f });
	}
	else if (cameraID == 2)
	{
		m_matrix.setTranslation(Vector3D{ 0.0f, 2.0f, 0.0f });
		SetPosition(Vector3D{ 0.0f, 2.0f, 0.0f });
	}
	else if (cameraID == 3)
	{
		m_matrix.setTranslation(Vector3D{ 0.0f, -2.0f, 0.0f });
		SetPosition(Vector3D{ 0.0f, -2.0f, 0.0f });
	}
	this->UpdateViewMatrix();
	// subscribe this class to the BNS_InputSystem
	BNS_InputSystem::get()->addListener(this);

	m_play_state = true;
}

BNS_Camera::~BNS_Camera()
{
	BNS_InputSystem::get()->removeListener(this);
}

void BNS_Camera::Update(float deltaTime, BNS_AppWindow* app_window)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	static bool isAppWindowAssign = false;
	if (!isAppWindowAssign)
	{
		isAppWindowAssign = true;
		m_app_window = app_window;
	}

	UpdateViewMatrix();
}

Matrix4x4 BNS_Camera::GetCamViewMatrix()
{
	return m_view_cam;
}

Matrix4x4 BNS_Camera::GetCurrentProjMatrix()
{
	// setting for the ort
	if (isPerspectiveMode)
		return GetCamPerspectiveMatrix();
	return GetCameraOrthoMatrix();
}

Matrix4x4 BNS_Camera::GetCameraOrthoMatrix()
{
	// setting for the orthographic projection
	Matrix4x4 orthoMatrix;
	orthoMatrix.setOrthoLH
	(
		BNS_UIManager::SCENE_VIEW_WIDTH / 300.0f,
		BNS_UIManager::SCENE_VIEW_HEIGHT / 300.0f,
		cam_properties.nearPlane,
		cam_properties.farPlane
	);

	

	return orthoMatrix;
}

Matrix4x4 BNS_Camera::GetCamPerspectiveMatrix()
{
	Matrix4x4 projectionMatrix;
	projectionMatrix.setPerspectiveFovLH(cam_properties.fovInDegrees * (3.1415926f / 180.0f), cam_properties.aspectRatio, cam_properties.nearPlane, cam_properties.farPlane);

	return projectionMatrix;
}

void BNS_Camera::UpdateViewMatrix()
{
	Matrix4x4 world_cam; world_cam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();
	// scale first
	temp.setScale(m_scale);
	world_cam *= temp;
	// rotation 
	Vector3D localRot = this->GetLocalRotation();
	temp.setRotationX(localRot.m_x);
	world_cam *= temp;
	temp.setRotationY(localRot.m_y);
	world_cam *= temp;
	temp.setRotationZ(localRot.m_z);
	world_cam *= temp;
	// position next
	// moving or setting the camera position in the x,y,z axis
	Vector3D new_pos = m_matrix.getTranslation() + world_cam.getZDirection() * (m_forward * 1.0f);
	new_pos = new_pos + world_cam.getYDirection() * (m_upward * 1.0f);
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 1.0f);
	temp.setTranslation(new_pos);
	world_cam *= temp;
	m_matrix = world_cam;

	// convert camera matrix to view matrix
	world_cam.inverse();
	m_view_cam = world_cam;

}

void BNS_Camera::onKeyDown(int key)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	Vector3D localPos = this->GetLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;
	if (key == 'W')
	{
		z += BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_forward = 1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
	else if (key == 'S')
	{
		z -= BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_forward = -1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
	else if (key == 'A')
	{
		x -= BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_rightward = -1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
	else if (key == 'D')
	{
		x += BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_rightward = 1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
	else if (key == 'E')
	{
		y += BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_upward = 1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
	else if (key == 'Q')
	{
		y -= BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
		SetPosition(x, y, z);
		UpdateViewMatrix();
		m_upward = -1.0f * BNS_EngineTime::getDeltaTime() * NAVIGATE_SPEED;
	}
}

void BNS_Camera::onKeyUp(int key)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	m_upward = 0.0f;
	m_forward = 0.0f;
	m_rightward = 0.0f;

	if (key == 'G')
	{
		m_play_state = (m_play_state) ? false : true;
	}
	if (key == 'F')
	{
		m_fullscreen_state = (m_fullscreen_state) ? false : true;
		RECT size_screen = m_app_window->getSizeScreen();
		m_app_window->m_swap_chain->setFullScreen(m_fullscreen_state,
			size_screen.right, size_screen.bottom);
		
	}
}

void BNS_Camera::onMouseMove(const Point& mouse_pos)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	if (!m_play_state) return;

	if (this->mouseDown) {
		float x = GetLocalRotation().m_x;
		float y = GetLocalRotation().m_y;
		float z = GetLocalRotation().m_z;

		float speed = 0.1f;
		x += (mouse_pos.m_y - (BNS_UIManager::WINDOW_HEIGHT / 2.0f)) * BNS_EngineTime::getDeltaTime() * speed;
		y += (mouse_pos.m_x - (BNS_UIManager::WINDOW_WIDTH / 2.0f)) * BNS_EngineTime::getDeltaTime() * speed;
		
		BNS_InputSystem::get()->setCursorPosition(Point((int)(BNS_UIManager::WINDOW_WIDTH / 2.0f),
			(int)(BNS_UIManager::WINDOW_HEIGHT / 2.0f)));

		
		SetRotation(x, y, z);
		UpdateViewMatrix();
	}
}

void BNS_Camera::onLeftMouseDown(const Point& delta_mouse_pos)
{
}

void BNS_Camera::onLeftMouseUp(const Point& delta_mouse_pos)
{
}

void BNS_Camera::onRightMouseDown(const Point& delta_mouse_pos)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	mouseDown = true;
	// hides the cursor
	BNS_InputSystem::get()->showCursor(false);
}

void BNS_Camera::onRightMouseUp(const Point& delta_mouse_pos)
{
	// if this camera is not used
	if (BNS_CameraHandler::GetInstance()->currentCamIndex != cameraID)
		return;

	mouseDown = false;
	// displays the cursor
	BNS_InputSystem::get()->showCursor(true);
}

bool BNS_Camera::IsPerspectiveMode()
{
	return isPerspectiveMode;
}

void BNS_Camera::SetPerspectiveMode(bool isPerspective)
{
	isPerspectiveMode = isPerspective;
}

BNS_Cam_Struct& BNS_Camera::GetCamProperties()
{
	return cam_properties;
}
