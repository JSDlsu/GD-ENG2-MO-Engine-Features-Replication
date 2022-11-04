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
	Matrix4x4 GetSceneCameraOrthographicMatrix();
	Matrix4x4 GetSceneCameraProjectionMatrix();
	Matrix4x4 GetSceneCameraMatrix();
	
};

