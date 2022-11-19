#include "BNS_CameraHandler.h"

#include "BNS_Camera.h"

BNS_CameraHandler* BNS_CameraHandler::sharedInstance = nullptr;

BNS_CameraHandler::BNS_CameraHandler()
{
    BNS_Camera* cameraPtr(new BNS_Camera("BNS_Camera", BNS_ObjectTypes::CAMERA));
    this->sceneCamera = cameraPtr;
}

BNS_CameraHandler::~BNS_CameraHandler()
{
    delete sceneCamera;
    delete sharedInstance;
}

void BNS_CameraHandler::Initialize()
{
    sharedInstance = new BNS_CameraHandler();
}

BNS_CameraHandler* BNS_CameraHandler::GetInstance()
{
    return sharedInstance;
}

Matrix4x4 BNS_CameraHandler::GetSceneCameraViewMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCamViewMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraProjMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCurrentProjMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraOrthoMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCameraOrthoMatrix();
}
Matrix4x4 BNS_CameraHandler::GetSceneCameraPerspecMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetCamPerspectiveMatrix();
}

Matrix4x4 BNS_CameraHandler::GetSceneCameraMatrix()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetMatrix();
}

Vector3D BNS_CameraHandler::GetSceneCameraPos()
{
    return dynamic_cast<BNS_Camera*>(&*sceneCamera)->GetLocalPosition();
}

BNS_Camera* BNS_CameraHandler::GetSceneCamera()
{
    return sceneCamera;
}
