#pragma once
#include "Matrix4x4.h"
#include "Prerequisites.h"

class Camera;

class CameraHandler
{
private:
	CameraHandler();
	~CameraHandler();
	CameraHandler(CameraHandler const&) {}; // copy constructor is private
	CameraHandler& operator=(CameraHandler const&) {}; // assignment operator is private

	static CameraHandler* sharedInstance;
private:
	CameraPtr sceneCamera;
public:
	static void Initialize();
	static CameraHandler* GetInstance();
public:
	Matrix4x4 GetSceneCameraViewMatrix();
	Matrix4x4 GetSceneCameraOrthoMatrix();
	Matrix4x4 GetSceneCameraProjMatrix();
	Matrix4x4 GetSceneCameraMatrix();
	Vector3D GetSceneCameraPos();
};

