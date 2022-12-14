#pragma once
#include <vector>

#include "Matrix4x4.h"
#include "BNS_Prerequisites.h"

class BNS_Camera;

class BNS_CameraHandler
{
private:
	BNS_CameraHandler();
	~BNS_CameraHandler();
	BNS_CameraHandler(BNS_CameraHandler const&) {}; // copy constructor is private
	BNS_CameraHandler& operator=(BNS_CameraHandler const&) {}; // assignment operator is private

	static BNS_CameraHandler* sharedInstance;
private:
	std::vector<BNS_Camera*> sceneCameras;
public:
	static void Initialize();
	static BNS_CameraHandler* GetInstance();
public:
	Matrix4x4 GetSceneCameraViewMatrix();
	Matrix4x4 GetSceneCameraProjMatrix();
	Matrix4x4 GetSceneCameraOrthoMatrix();
	Matrix4x4 GetSceneCameraPerspecMatrix();
	Matrix4x4 GetSceneCameraMatrix();
	Vector3D GetSceneCameraPos();
	BNS_Camera* GetSceneCamera();

public:
	int currentCamIndex = 0;
};

