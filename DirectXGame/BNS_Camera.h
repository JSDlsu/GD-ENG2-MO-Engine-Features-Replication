#pragma once
#include "BNS_AGameObject.h"
#include "BNS_InputListener.h"
#include "BNS_StructHandler.h"
#include "BNS_UIManager.h"

class Point;



class BNS_Camera : public BNS_AGameObject, public BNS_InputListener
{
public:
	BNS_Camera(std::string name, BNS_ObjectTypes type, int cameraID);
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
private:
	float m_upward = 0.0f;
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	bool mouseDown = false;
	const float NAVIGATE_SPEED = 2.5f;
	bool isPerspectiveMode = true;
	bool m_play_state = false;
	bool m_fullscreen_state = false;
private:
	Matrix4x4 m_view_cam;
	BNS_Cam_Struct cam_properties;
	BNS_AppWindow* m_app_window = nullptr;
public:
	//NEW: FOR TRANSFERRING PROJECTION MATRIX TO CAM INSTEAD OF INDIVIDUAL PRIMS
	Matrix4x4 m_proj_cam;
	int cameraID = -1;
public:
	bool IsPerspectiveMode();
	void SetPerspectiveMode(bool isPerspective = true);
	BNS_Cam_Struct& GetCamProperties();

};

