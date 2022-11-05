#include "CameraHandler.h"

#include "Camera.h"

CameraHandler* CameraHandler::sharedInstance = nullptr;

CameraHandler::CameraHandler()
{
    CameraPtr cameraPtr(new Camera("Camera", ObjectTypes::CAMERA));
    this->sceneCamera = cameraPtr;
}

CameraHandler::~CameraHandler()
{
    delete sharedInstance;
}

void CameraHandler::Initialize()
{
    sharedInstance = new CameraHandler();
}

CameraHandler* CameraHandler::GetInstance()
{
    return sharedInstance;
}

Matrix4x4 CameraHandler::GetSceneCameraViewMatrix()
{
    return dynamic_cast<Camera*>(&*sceneCamera)->GetCamViewMatrix();
}
Matrix4x4 CameraHandler::GetSceneCameraOrthoMatrix()
{
    return dynamic_cast<Camera*>(&*sceneCamera)->GetCameraOrthoMatrix();
}
Matrix4x4 CameraHandler::GetSceneCameraProjMatrix()
{
    return dynamic_cast<Camera*>(&*sceneCamera)->GetCamProjectionMatrix();
}

Matrix4x4 CameraHandler::GetSceneCameraMatrix()
{
    return dynamic_cast<Camera*>(&*sceneCamera)->GetMatrix();
}

Vector3D CameraHandler::GetSceneCameraPos()
{
    return dynamic_cast<Camera*>(&*sceneCamera)->GetLocalPosition();
}
