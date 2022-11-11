#pragma once
#include "BNS_AGameObject.h"
#include "BNS_InputListener.h"
#include "BNS_UIManager.h"

class Point;



class BNS_Camera : public BNS_AGameObject, public BNS_InputListener
{
public:
	BNS_Camera(std::string name, BNS_ObjectTypes type);
	~BNS_Camera();
public:
	void Update(float deltaTime, BNS_AppWindow* app_window) override;

	Matrix4x4 GetCamViewMatrix();
	Matrix4x4 GetCurrentProjMatrix();
	Matrix4x4 GetCameraOrthoMatrix();
	Matrix4x4 GetCamPerspectiveMatrix();
	void UpdateViewMatrix();

	void onKeyDown(int key) override;
	void onKeyUp(int key) override;
	void onMouseMove(const Point& mouse_pos) override;
	void onLeftMouseDown(const Point& delta_mouse_pos) override;
	void onLeftMouseUp(const Point& delta_mouse_pos) override;
	void onRightMouseDown(const Point& delta_mouse_pos) override;
	void onRightMouseUp(const Point& delta_mouse_pos) override;
public:
	float m_upward = 0.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	bool mouseDown = false;
	const float NAVIGATE_SPEED = 2.5f;
	Matrix4x4 m_view_cam;
	//NEW: FOR TRANSFERRING PROJECTION MATRIX TO CAM INSTEAD OF INDIVIDUAL PRIMS
	Matrix4x4 m_proj_cam;
	float fovInDegrees = 90.0f;
	float nearPlane = 0.1f;
	float farPlane = 100.0f;
	float fovValue = (3.1415926f / 180.0f);
	float aspectRatio = BNS_UIManager::WINDOW_WIDTH / BNS_UIManager::WINDOW_HEIGHT;
	float fov = fovInDegrees * fovValue;

	float Oheight = BNS_UIManager::WINDOW_WIDTH / 300.0f;
	float Owidth = BNS_UIManager::WINDOW_HEIGHT / 300.0f;
	
private:
	bool isPerspectiveMode = true;
public:
	bool IsPerspectiveMode();
	void SetPerspectiveMode(bool isPerspective = true);

};

